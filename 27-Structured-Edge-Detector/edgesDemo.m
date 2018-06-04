% Demo for Structured Edge Detector (please see readme.txt first).

%% set opts for training (see edgesTrain.m)
opts=edgesTrain();                % default options (good settings)
opts.modelDir='models/';          % model will be in models/forest
opts.modelFnm='modelBsds';        % model name
opts.nPos=5e5; opts.nNeg=5e5;     % decrease to speedup training
opts.useParfor=0;                 % parallelize if sufficient memory

%% train edge detector (~20m/8Gb per tree, proportional to nPos/nNeg)
tic, model=edgesTrain(opts); toc; % will load model if already trained

%% set detection parameters (can set after training)
model.opts.multiscale=1;          % for top accuracy set multiscale=1
model.opts.sharpen=0;             % for top speed set sharpen=0
model.opts.nTreesEval=1;          % for top speed set nTreesEval=1
model.opts.nThreads=4;            % max number threads for evaluation
model.opts.nms=1;                 % set to true to enable nms

%% evaluate edge detector on BSDS500 (see edgesEval.m)
if(0), edgesEval( model, 'show',1, 'name','' ); end

%% detect edge and visualize results
filename = 'C:\Users\lvpal\Desktop\Abinaya\EE569_hw3_images\EE569_hw3_images\Animal.jpg';
I = imread(filename);
tic, E=edgesDetect(I,model); toc
figure(1); im(I);
title('Input Image');
figure(2); im(1-E);
title('Structured Edge Probability Map');

%% Binarize based on threshold
threshold = 0.15;
im_size = size(E);
for i=1:im_size(1)
    for j=1:im_size(2)
        if E(i,j) > threshold
            I_edge(i,j) = 0;
        else
            I_edge(i,j) = 255;
        end
    end
end
figure(); imshow(I_edge);
title(['Structured Edge: Binary Map with threshold = ' num2str(threshold)]);

%% Evaluation for every ground truth
ground_truth_filename = 'C:\Users\lvpal\Desktop\Abinaya\EE569_hw3_images\EE569_hw3_images\Animal.mat';
gt = load(ground_truth_filename);
n_gt = 5;
recall_array = [];
precision_array = [];
for i=1:n_gt
    [thrs,cntR,sumR,cntP,sumP,V] = edgesEvalImg(E,gt.groundTruth{i}.Boundaries); 
    R_array = cntR./sumR;
    P_array = cntP./sumP;
    F_array = 2 * ((P_array .* R_array)./(P_array + R_array));
    [max_value, max_index] = max(F_array)
    recall = R_array(max_index);
    precision = P_array(max_index);
    recall_array(i) = recall;
    precision_array(i) = precision;
end

recall_array
precision_array
mean_recall = mean(recall_array)
mean_precision = mean(precision_array)
F_measure = 2 * ((mean_precision * mean_recall)/(mean_precision + mean_recall))


