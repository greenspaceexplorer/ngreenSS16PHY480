dir_name = '/home/noah/Dropbox/git-repos/ngreenSS16PHY480/Project4/code/top_pt_230-240/';
directory = dir(dir_name);
nfile = length(directory(not([directory.isdir])));
for i=1:nfile+2
   if not(directory(i).isdir)
    M = csvread(strcat(dir_name,directory(i).name));
    rad_M = max(max(M));
    [I,J] = rca1dm(M,rad_M);
    h0_diag = strcat(directory(i).name,'_H0.pdf');
    h1_diag = strcat(directory(i).name,'_H1.pdf');
    figure('Visible','off'),plotpersistencediagram(I);
    %h0,plotpersistencediagram(J);
    hold off   
    saveas(gcf,h1_diag);
    clf;
    plotpersistencediagram(J);
    saveas(gcf,h0_diag);
    clear M;
    clear I;
    clear J;
   end
end