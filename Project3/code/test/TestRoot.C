# include <iostream>
# include <TGraph.h>
# include <TCanvas.h>

using namespace std;

void hello()
{
  cout << "hello world!" << endl;

  TCanvas *c1 = new TCanvas("c1","A Simple Graph Example",200,10,700,500);
  c1->cd();
   Double_t x[100], y[100];
   Int_t n = 20;
   for (Int_t i=0;i<n;i++) {
     x[i] = i*0.1;
     y[i] = 10*sin(x[i]+0.2);
   }
   TGraph *gr = new TGraph(n,x,y);
   gr->Draw("AC*");
   c1->Print("testdraw.pdf");
}

# ifndef __CINT__
int main()
{
  hello();
  return 0;
}
# endif
