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
#include <ROOT/TTreeReader.h>
#include <ROOT/TTreeReaderArray.h>

using namespace std;

int main(int argc, char *argv[])
{
    TFile *inputSignal = TFile::Open("HIGGSsignal.root", "READ");
    TTree *treeS = nullptr;
    inputSignal->GetObject("tree", treeS);

    int nEntries;
    if (argc > 1)
    {
        nEntries = atoi(argv[1]) / 2;
    }
    else
    {
        nEntries = (int)treeS->GetEntries();
    }
    // int nEntriesS = (int)treeS->GetEntries();

    TFile *inputBkg = TFile::Open("HIGGSbackground.root", "READ");
    TTree *treeB = nullptr;
    inputBkg->GetObject("tree", treeB);
    int nEntriesB = (int)treeB->GetEntries();

    vector<Double_t> vars(28);
    vector<string> var_names = {"lepton_pT", "lepton_eta", "lepton_phi", "missing_energy_magnitude", "missing_energy_phi",
                                "jet_1_pt", "jet_1_eta", "jet_1_phi", "jet_1_b_tag", "jet_2_pt", "jet_2_eta", "jet_2_phi", "jet_2_b_tag",
                                "jet_3_pt", "jet_3_eta", "jet_3_phi", "jet_3_b_tag", "jet_4_pt", "jet_4_eta", "jet_4_phi", "jet_4_b_tag",
                                "m_jj", "m_jjj", "m_lv", "m_jlv", "m_bb", "m_wbb", "m_wwbb"};

    // // Set up reading from the TTree
    // TTreeReader reader(treeS);
    // // TTreeReaderArray<double> lep_pt(reader, "lepton_pT");
    // vector<TTreeReaderArray<double>> readers;
    // // double entries = reader.GetEntries(true);
    // for (int i = 0; i < 28; i++)
    // {
    //     readers.emplace_back(reader, var_names[i].c_str());
    // }

    // while (reader.Next())
    // {
    //     reader.Next();
    //     for (int i = 0, n = readers[0].GetSize(); i < n; ++i)
    //     {
    //         cout << readers[1][i] << endl;
    //     }
    // }

    for (int i = 0; i < 28; i++)
    {
        treeS->SetBranchAddress(var_names[i].c_str(), &vars[i]);
        treeB->SetBranchAddress(var_names[i].c_str(), &vars[i]);
    }

    TFile *outputfile = TFile::Open("higgs_small.root", "recreate");

    TTree *signalTree = new TTree("TreeS", "TreeS");
    TTree *bkgTree = new TTree("TreeB", "TreeB");

    for (int i = 0; i < 28; i++)
    {
        signalTree->Branch(var_names[i].c_str(), &vars[i]);
        bkgTree->Branch(var_names[i].c_str(), &vars[i]);
    }

    ofstream out_file;
    out_file.open("higgs_small.txt");
    for (int i = 0; i < 28; i++)
    {
        out_file << var_names[i] << ",";
    }
    out_file << "label\n";

    for (int iEntry = 0; iEntry < nEntries; iEntry++)
    {
        treeS->GetEntry(iEntry);
        for (int i = 0; i < 28; i++)
        {
            out_file << vars[i] << ",";
        }
        out_file << 1 << "\n";
        signalTree->Fill();
    }
    for (int iEntry = 0; iEntry < nEntries; iEntry++)
    {
        treeB->GetEntry(iEntry);
        for (int i = 0; i < 28; i++)
        {
            out_file << vars[i] << ",";
        }
        out_file << 0 << "\n";
        bkgTree->Fill();
    }

    outputfile->Write();
    outputfile->Close();
    inputSignal->Close();
    inputBkg->Close();
    out_file.close();
    return 0;
}