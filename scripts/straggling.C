void straggling()
{
    TFile *f = new TFile("../build/output0.root");

    if (!f->IsOpen())
    {
        std::cerr << "Error: File not found!" << std::endl;
        return;
    }

    TCanvas *c = new TCanvas("c", "c", 800, 600);

    c->SetLogy();

    TH1F *hist = (TH1F *)f->Get("Angle;1");

    hist->SetFillColor(kYellow);
    hist->SetTitle("Angle;#theta;Counts");
    hist->Draw("hist");

    c->Print("../build/angle1.png");
    c->Print("../build/angle1.pdf");
}