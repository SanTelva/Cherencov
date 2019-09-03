TCanvas* graph()
{
//   gStyle->SetOptStat(0);
//   gStyle->SetOptFit();
   gStyle->SetPalette(0);

   TCanvas *c = new TCanvas("c","C FF=1 Recoil nuclear energy - angular distribution",0,0,1000,1000);
//   c->Divide(1,2);
   Int_t nlines = 0,  itype,  nev,nevold;
   Float_t x0,y0,z0,cx,cy,cz,e0,   x,y,z,t,e,  range;
   ifstream in;



//  ********************************************************************

//   c->cd(1);

//   in.open("rand-dRdEdcosT-FF-C-400");
//   in.open("rand-dRdEdcosT-FF-Br-400");
//   in.open("rand-dRdEdcosT-H-400");
//   in.open("rand-dRdEdcosT-FF-Br-220");
//   in.open("rand-dRdEdcosT-FF-Br-800");
//   in.open("rand-dRdEdcosT-FF-Br-60-220-20");

//   in.open("rand-dRdEdcosT-FF-Br-60-220-156");
//     in.open("rand-dRdEdcosT-FF-Br-60-220-156-thr40keV");
//     in.open("rand-dRdEdcosT-FF-Br-60-220-156-thr5keV");     
//      in.open("rand-dRdEdcosT-H-220");

// in.open("rand-dRdEdcosT-FF-C-60-220-156");
 in.open("rand-dRdEdcosT-FF-H-60-220-156");
   
//   TH2F *h1 = new TH2F("n", "Br ,v=220, CosTet_E_R, FF=Helm, Spin Dependence",
//   TH2F *h1 = new TH2F("n", "Br ,v=220(20), CosTet_E_R, FF=Helm, Spin Dependence",
//  TH2F *h1 = new TH2F("n", "Br ,v=220(156), thr=0, CosTet_E_R, FF=Helm, Spin Dependence",
  
//   TH2F *h1 = new TH2F("n", "C ,v=220(156), thr=0, CosTet_E_R, FF=Helm, Spin Dependence",
   TH2F *h1 = new TH2F("n", "H ,v=220(156), thr=0, CosTet_E_R, FF=1, Spin Dependence",
   
//   TH2F *h1 = new TH2F("n", "Br ,v=220(156), thr=40keV, CosTet_E_R, FF=Helm, Spin Dependence",   
//   TH2F *h1 = new TH2F("n", "Br ,v=220(156), thr=5keV, CosTet_E_R, FF=Helm, Spin Dependence",      
//   TH2F *h1 = new TH2F("n", "H ,v=220, CosTet_E_R, FF=1, Spin Dependence",   
//                      200,0.0,1.0,200,0.0,1000.0);
//    Br, Ar                      50,0.0,1.0,50,0.0,30.0);
                      30,0.0,1.0,30,0.0,10.0);
//                      30,0.0,1.0,30,0.0,60.0);
//                   30,0.0,1.0,30,20.0,150.0);

   nlines = 0;
//   nev = 1;
   while(1) {
//   while(nev == 1) {
     in >>  x >> y;
   printf(" >>>> x=%7.6e, y=%7.6e \n",x,y);
     if (!in.good())  break;
     h1->Fill(x,y);
//     h1->Fill(t*0.001,e);
     nlines++;
   }
//   h1->Fill(log(t*0.001),log(e));
   printf(" ***** Recoil: Found %d entries\n",nlines);
   in.close();

   h1->SetFillColor(kGreen);
   h1->GetXaxis()->SetTitle("CosTetta");
   h1->GetXaxis()->SetTitleOffset(1.6);
   h1->GetXaxis()->SetTitleSize(0.030);
//   h1->GetXaxis()->SetTitle("t, uS");
   h1->GetXaxis()->SetLabelSize(0.020);
   h1->GetXaxis()->SetNdivisions(205);

   h1->GetYaxis()->SetTitle("Ekin, keV");
   h1->GetYaxis()->SetTitleOffset(1.6);
   h1->GetYaxis()->SetTitleSize(0.030);
//   h1->GetYaxis()->SetTitle("Ekin, keV");
   h1->GetYaxis()->SetLabelSize(0.020);
   h1->GetYaxis()->SetNdivisions(205);

   h1->GetXaxis()->CenterTitle();
   h1->GetYaxis()->CenterTitle();
   h1->GetZaxis()->SetLabelSize(0.020);

   h1->Draw("LEGO2Z");
//   h1->Draw("CONTZ");



   return c;
}
