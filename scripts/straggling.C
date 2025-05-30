void straggling()
{
    gROOT->ForceStyle();

    TFile *f = new TFile("../build/output0.root");

    if (!f->IsOpen())
    {
        std::cerr << "Error: File not found!" << std::endl;
        return;
    }

    TCanvas *c = new TCanvas("c", "c", 800, 600);

    c->SetLogy();

    TH1F *hist = (TH1F *)f->Get("Angle;1");

    double rms = hist->GetRMS();
    double mean = hist->GetMean();

    hist->SetFillColor(kYellow);
    hist->SetTitle("Cherenkov Angle in Fused Silica;#theta [rad];Counts");
    hist->Draw("hist");
    //hist->GetXaxis()->SetRangeUser(mean - 25 * rms, mean + 25 * rms);


    c->Print("../build/angle1.png");
    c->Print("../build/angle1.pdf");
}