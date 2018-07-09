/* In order to compile this script use 
g++ conv.cpp `root-config --cflags --glibs`
*/

#include <fstream>
#include <time.h>
#include <cmath>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>
#include <algorithm>
#include <ROOT/TTree.h>
#include <ROOT/TFile.h>
#include <ROOT/TH1.h>
#include <ROOT/TCanvas.h>
#include <ROOT/TCanvas.h>
#include <ROOT/TLorentzVector.h>

using namespace std;

int main()
{
    TFile *inputSignal = TFile::Open("HIGGSsignal.root", "READ");
    TTree *treeS = nullptr;
    inputSignal->GetObject("tree", treeS);
    int nEntriesS = (int)treeS->GetEntries();
    TFile *inputBkg = TFile::Open("HIGGSbackground.root", "READ");
    TTree *treeB = nullptr;
    inputBkg->GetObject("tree", treeB);
    int nEntriesB = (int)treeB->GetEntries();
    Double_t lepton_pT;
    Double_t lepton_eta;
    Double_t lepton_phi;
    Double_t missing_energy_magnitude;
    Double_t missing_energy_phi;
    Double_t jet_1_pt;
    Double_t jet_1_eta;
    Double_t jet_1_phi;
    Double_t jet_1_b_tag;
    Double_t jet_2_pt;
    Double_t jet_2_eta;
    Double_t jet_2_phi;
    Double_t jet_2_b_tag;
    Double_t jet_3_pt;
    Double_t jet_3_eta;
    Double_t jet_3_phi;
    Double_t jet_3_b_tag;
    Double_t jet_4_pt;
    Double_t jet_4_eta;
    Double_t jet_4_phi;
    Double_t jet_4_b_tag;
    Double_t m_jj;
    Double_t m_jjj;
    Double_t m_lv;
    Double_t m_jlv;
    Double_t m_bb;
    Double_t m_wbb;
    Double_t m_wwbb;
    treeS->SetBranchAddress("lepton_pT", &lepton_pT);
    treeS->SetBranchAddress("lepton_eta", &lepton_eta);
    treeS->SetBranchAddress("lepton_phi", &lepton_phi);
    treeS->SetBranchAddress("missing_energy_magnitude", &missing_energy_magnitude);
    treeS->SetBranchAddress("missing_energy_phi", &missing_energy_phi);
    treeS->SetBranchAddress("jet_1_pt", &jet_1_pt);
    treeS->SetBranchAddress("jet_1_eta", &jet_1_eta);
    treeS->SetBranchAddress("jet_1_phi", &jet_1_phi);
    treeS->SetBranchAddress("jet_1_b_tag", &jet_1_b_tag);
    treeS->SetBranchAddress("jet_2_pt", &jet_2_pt);
    treeS->SetBranchAddress("jet_2_eta", &jet_2_eta);
    treeS->SetBranchAddress("jet_2_phi", &jet_2_phi);
    treeS->SetBranchAddress("jet_2_b_tag", &jet_2_b_tag);
    treeS->SetBranchAddress("jet_3_pt", &jet_3_pt);
    treeS->SetBranchAddress("jet_3_eta", &jet_3_eta);
    treeS->SetBranchAddress("jet_3_phi", &jet_3_phi);
    treeS->SetBranchAddress("jet_3_b_tag", &jet_3_b_tag);
    treeS->SetBranchAddress("jet_4_pt", &jet_4_pt);
    treeS->SetBranchAddress("jet_4_eta", &jet_4_eta);
    treeS->SetBranchAddress("jet_4_phi", &jet_4_phi);
    treeS->SetBranchAddress("jet_4_b_tag", &jet_4_b_tag);
    treeS->SetBranchAddress("m_jj", &m_jj);
    treeS->SetBranchAddress("m_jjj", &m_jjj);
    treeS->SetBranchAddress("m_lv", &m_lv);
    treeS->SetBranchAddress("m_jlv", &m_jlv);
    treeS->SetBranchAddress("m_bb", &m_bb);
    treeS->SetBranchAddress("m_wbb", &m_wbb);
    treeS->SetBranchAddress("m_wwbb", &m_wwbb);

    treeB->SetBranchAddress("lepton_pT", &lepton_pT);
    treeB->SetBranchAddress("lepton_eta", &lepton_eta);
    treeB->SetBranchAddress("lepton_phi", &lepton_phi);
    treeB->SetBranchAddress("missing_energy_magnitude", &missing_energy_magnitude);
    treeB->SetBranchAddress("missing_energy_phi", &missing_energy_phi);
    treeB->SetBranchAddress("jet_1_pt", &jet_1_pt);
    treeB->SetBranchAddress("jet_1_eta", &jet_1_eta);
    treeB->SetBranchAddress("jet_1_phi", &jet_1_phi);
    treeB->SetBranchAddress("jet_1_b_tag", &jet_1_b_tag);
    treeB->SetBranchAddress("jet_2_pt", &jet_2_pt);
    treeB->SetBranchAddress("jet_2_eta", &jet_2_eta);
    treeB->SetBranchAddress("jet_2_phi", &jet_2_phi);
    treeB->SetBranchAddress("jet_2_b_tag", &jet_2_b_tag);
    treeB->SetBranchAddress("jet_3_pt", &jet_3_pt);
    treeB->SetBranchAddress("jet_3_eta", &jet_3_eta);
    treeB->SetBranchAddress("jet_3_phi", &jet_3_phi);
    treeB->SetBranchAddress("jet_3_b_tag", &jet_3_b_tag);
    treeB->SetBranchAddress("jet_4_pt", &jet_4_pt);
    treeB->SetBranchAddress("jet_4_eta", &jet_4_eta);
    treeB->SetBranchAddress("jet_4_phi", &jet_4_phi);
    treeB->SetBranchAddress("jet_4_b_tag", &jet_4_b_tag);
    treeB->SetBranchAddress("m_jj", &m_jj);
    treeB->SetBranchAddress("m_jjj", &m_jjj);
    treeB->SetBranchAddress("m_lv", &m_lv);
    treeB->SetBranchAddress("m_jlv", &m_jlv);
    treeB->SetBranchAddress("m_bb", &m_bb);
    treeB->SetBranchAddress("m_wbb", &m_wbb);
    treeB->SetBranchAddress("m_wwbb", &m_wwbb);

    TFile *outputfile = TFile::Open("higgs_small.root", "recreate");

    TTree *signalTree = new TTree("TreeS", "TreeS");
    TTree *bkgTree = new TTree("TreeB", "TreeB");

    signalTree->Branch("lepton_pT", &lepton_pT);
    signalTree->Branch("lepton_eta", &lepton_eta);
    signalTree->Branch("lepton_phi", &lepton_phi);
    signalTree->Branch("missing_energy_magnitude", &missing_energy_magnitude);
    signalTree->Branch("missing_energy_phi", &missing_energy_phi);
    signalTree->Branch("jet_1_pt", &jet_1_pt);
    signalTree->Branch("jet_1_eta", &jet_1_eta);
    signalTree->Branch("jet_1_phi", &jet_1_phi);
    signalTree->Branch("jet_1_b_tag", &jet_1_b_tag);
    signalTree->Branch("jet_2_pt", &jet_2_pt);
    signalTree->Branch("jet_2_eta", &jet_2_eta);
    signalTree->Branch("jet_2_phi", &jet_2_phi);
    signalTree->Branch("jet_2_b_tag", &jet_2_b_tag);
    signalTree->Branch("jet_3_pt", &jet_3_pt);
    signalTree->Branch("jet_3_eta", &jet_3_eta);
    signalTree->Branch("jet_3_phi", &jet_3_phi);
    signalTree->Branch("jet_3_b_tag", &jet_3_b_tag);
    signalTree->Branch("jet_4_pt", &jet_4_pt);
    signalTree->Branch("jet_4_eta", &jet_4_eta);
    signalTree->Branch("jet_4_phi", &jet_4_phi);
    signalTree->Branch("jet_4_b_tag", &jet_4_b_tag);
    signalTree->Branch("m_jj", &m_jj);
    signalTree->Branch("m_jjj", &m_jjj);
    signalTree->Branch("m_lv", &m_lv);
    signalTree->Branch("m_jlv", &m_jlv);
    signalTree->Branch("m_bb", &m_bb);
    signalTree->Branch("m_wbb", &m_wbb);
    signalTree->Branch("m_wwbb", &m_wwbb);

    bkgTree->Branch("lepton_pT", &lepton_pT);
    bkgTree->Branch("lepton_eta", &lepton_eta);
    bkgTree->Branch("lepton_phi", &lepton_phi);
    bkgTree->Branch("missing_energy_magnitude", &missing_energy_magnitude);
    bkgTree->Branch("missing_energy_phi", &missing_energy_phi);
    bkgTree->Branch("jet_1_pt", &jet_1_pt);
    bkgTree->Branch("jet_1_eta", &jet_1_eta);
    bkgTree->Branch("jet_1_phi", &jet_1_phi);
    bkgTree->Branch("jet_1_b_tag", &jet_1_b_tag);
    bkgTree->Branch("jet_2_pt", &jet_2_pt);
    bkgTree->Branch("jet_2_eta", &jet_2_eta);
    bkgTree->Branch("jet_2_phi", &jet_2_phi);
    bkgTree->Branch("jet_2_b_tag", &jet_2_b_tag);
    bkgTree->Branch("jet_3_pt", &jet_3_pt);
    bkgTree->Branch("jet_3_eta", &jet_3_eta);
    bkgTree->Branch("jet_3_phi", &jet_3_phi);
    bkgTree->Branch("jet_3_b_tag", &jet_3_b_tag);
    bkgTree->Branch("jet_4_pt", &jet_4_pt);
    bkgTree->Branch("jet_4_eta", &jet_4_eta);
    bkgTree->Branch("jet_4_phi", &jet_4_phi);
    bkgTree->Branch("jet_4_b_tag", &jet_4_b_tag);
    bkgTree->Branch("m_jj", &m_jj);
    bkgTree->Branch("m_jjj", &m_jjj);
    bkgTree->Branch("m_lv", &m_lv);
    bkgTree->Branch("m_jlv", &m_jlv);
    bkgTree->Branch("m_bb", &m_bb);
    bkgTree->Branch("m_wbb", &m_wbb);
    bkgTree->Branch("m_wwbb", &m_wwbb);

    ofstream out_file;
    out_file.open("higgs_small.txt");

    // TTree *backTree = new TTree("TreeB", "TreeB");
    out_file << "lepton_pT,lepton_eta,lepton_phi,met_magnitude,met_phi,jet_1_pt,jet_1_eta,jet_1_phi,jet_1_b_tag,jet_2_pt,jet_2_eta,jet_2_phi,jet_2_b_tag,jet_3_pt,jet_3_eta,jet_3_phi,jet_3_b_tag,jet_4_pt,jet_4_eta,jet_4_phi,jet_4_b_tag,m_jj,m_jjj,m_lv,m_jlv,m_bb,m_wbb,m_wwbb,label\n";
    for (int iEntry = 0; iEntry < nEntriesS / 100; iEntry++)
    {
        treeS->GetEntry(iEntry);
        out_file << lepton_pT << "," << lepton_eta << "," << lepton_phi << "," << missing_energy_magnitude << "," << missing_energy_phi << "," << jet_1_pt << "," << jet_1_eta << "," << jet_1_phi << "," << jet_1_b_tag << "," << jet_2_pt << "," << jet_2_eta << "," << jet_2_phi << "," << jet_2_b_tag << "," << jet_3_pt << "," << jet_3_eta << "," << jet_3_phi << "," << jet_3_b_tag << "," << jet_4_pt << "," << jet_4_eta << "," << jet_4_phi << "," << jet_4_b_tag << "," << m_jj << "," << m_jjj << "," << m_lv << "," << m_jlv << "," << m_bb << "," << m_wbb << "," << m_wwbb << "," << 1 << "\n";
        signalTree->Fill();
    }
    for (int iEntry = 0; iEntry < nEntriesB / 100; iEntry++)
    {
        treeB->GetEntry(iEntry);
        out_file << lepton_pT << "," << lepton_eta << "," << lepton_phi << "," << missing_energy_magnitude << "," << missing_energy_phi << "," << jet_1_pt << "," << jet_1_eta << "," << jet_1_phi << "," << jet_1_b_tag << "," << jet_2_pt << "," << jet_2_eta << "," << jet_2_phi << "," << jet_2_b_tag << "," << jet_3_pt << "," << jet_3_eta << "," << jet_3_phi << "," << jet_3_b_tag << "," << jet_4_pt << "," << jet_4_eta << "," << jet_4_phi << "," << jet_4_b_tag << "," << m_jj << "," << m_jjj << "," << m_lv << "," << m_jlv << "," << m_bb << "," << m_wbb << "," << m_wwbb << "," << 0 << "\n";
        bkgTree->Fill();
    }

    outputfile->Write();

    outputfile->Close();
    inputSignal->Close();
    inputBkg->Close();
    out_file.close();
    return 0;
}