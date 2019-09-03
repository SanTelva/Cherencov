TCanvas* graph()
{
// gStyle->SetOptStat(0);
// gStyle->SetOptFit();

   TCanvas *c = new TCanvas("c","WIMP",0,0,1000,1000);


   gStyle->SetPalette(1);
//   c->cd(1);
   gStyle->SetHistTopMargin(0);
// f2->Draw("surf1");
// dt->Draw("same p0");

//  Double_t x[90], y[90], z[90], zz[90];
    Double_t x[5000], y[5000], z[5000], zz[5000];
  Int_t n, i;
  
  ifstream in;

//  Absorbed dose per voxel, Gy
//  mcm

/*  
  n = 0;
  in.open("dep_en_map");
  while(1) {
    in >> x[n] >> y[n] >> z[n];
    printf(" z(n)=%f\n",z[n]);
//    z[n] *= 4.19e-6;    //  convert keV/pixel to Gy
//    z[n] *= 16.76e-6;    //  convert keV/pixel to Gy
    z[n] *= 1.07264e-3;    //  convert keV/pixel to Gy
    if(!in.good()) break;
    n ++;
  }
  printf(" *** dep_en_map: found %d entries\n",n);
  in.close();
*/

//   TGraph2D *ae = new TGraph2D(n,x,y,z);


// 27/02/2019    TGraph2D *ae = new TGraph2D("dRdEdcosTF");
//  TGraph2D *ae = new TGraph2D("dRdEdcosTF-1");  
//  TGraph2D *ae = new TGraph2D("dRdEdcosT-F-Ag");    

// TGraph2D *ae = new TGraph2D("dRdEdcosT-H-400-SID_SD");      
// TGraph2D *ae = new TGraph2D("dRdEdcosT-Br80-400-FF-SID");

//  TGraph2D *ae = new TGraph2D("dRdEdcosT-Br80-60-220-20-FF-SID_SD-j-3-2");
//  TGraph2D *ae = new TGraph2D("dRdEdcosT-Br80-60-220-156-FF-SID_SD-j-3-2");  
//  TGraph2D *ae = new TGraph2D("dRdEdcosT-Br80-60-220-15-6-FF-SID_SD-j-3-2");    
//  TGraph2D *ae = new TGraph2D("dRdEdcosT-H1-60-220-156-SD-j-1-2");  
    TGraph2D *ae = new TGraph2D("dRdEdcosT-H-220-SID_SD");  



 //    TGraph2D *ae = new TGraph2D("dRdEdcosT-C-400-func");      

//   ae->SetTitle("dR/(dEdcosT)+Form factor  X - cos(Teta),   Y  -  ER, keV  ");
//   ae->SetTitle("dR/(dEdcosT) Ag, Form factor=Helm,  X - cos(Teta), Y  -  ER, keV");   
//  ae->SetTitle("dR/(dEdcosT) H(1,1), SI(FF=1) + SD ,   X - cos(Teta), Y  -  ER, keV");   
//    ae->SetTitle("dR/(dEdcosT) Br(80,35), Spin dependence,  X - cos(Teta), Y  -  ER, keV");   

//    ae->SetTitle("dR/(dEdcosT) Br(80,35),FF-SD,220(20),mw=60, X - cos(Teta), Y  -  ER, keV");   
//    ae->SetTitle("dR/(dEdcosT) Br(80,35),FF-SD,220(156),mw=60, X - cos(Teta), Y  -  ER, keV");   
  ae->SetTitle("dR/(dEdcosT) H(1,1),SD,220(156),mw=60, X - cos(Teta), Y  -  ER, keV");   


//   ae->Draw("surf1z");
//   ae->Draw("same p0");

 ae->SetMarkerStyle(20);
// ae->SetMarkerColor(4);
     ae->SetMarkerColor(9);
// ae->SetMarkerColor(3); 

 ae->Draw("P");

//       ae->Draw("contz");

// ae->Draw("cont4z");

// ae->Draw("cont5z");
// ae->Draw("lego2z");

// ae->Draw("surf1z");
// ae->Draw("lego1z");

/*
   for(i=0; i<n; i++) {
     zz[i] = 0.000003; 
   }
   TGraph2D *g2 = new TGraph2D(n,x,y,zz);
   g2->SetMarkerStyle(20);
   g2->SetMarkerSize(0.8);
   g2->SetMarkerColor(1);

   g2->Draw("Psame");
*/

   return c;
}

//   1 pixel = 1 * 1 * 64 mcm3 = 64 mcm3,
//   1 keV/pixel = 4.19e-6 Gy * 256 = 1.07264e-3 Gy


//   1 pixel = 8 * 8 * 64 mcm3 = 4096 mcm3,
//   1 keV/pixel = 4.19e-6 Gy * 4 = 16.76e-6 Gy

//   1 keV/pixel = 6.1e-5 keV/mcm3,  1 keV = 1000 * 1.6e-19 J,  1 Gy = 1 J/kg,
//   1 pixel = 16 * 16 * 64 mcm3 = 16384 mcm3,
//   rho_Si = 2.33 g/cm3 = 2.33 * 1e-3 kg * (10000 mcm)^(-3) = 2.33 * 10^(-15) kg/mcm3
//   1 keV/pixel = 1.6e-16 J / (16384 * rho_Si) = 1.6e-16 J / (16384 *2.33e-15 kg) =
//   = 1.6-16 J / 38174,72e-15 kg = 4.19e-6 J/kg = 4.19e-6 Gy
