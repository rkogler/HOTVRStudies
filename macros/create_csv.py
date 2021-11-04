import os,sys,csv
from ROOT import TFile,TTree

nevents_max = 300000

csv_qcd = "/nfs/dust/cms/user/albrecha/uhh2_102X_v2/HOTVRStudiesOutput/HOTVR_ML/qcd_constituents_VR_08_04.csv"

csv_ttbar = "/nfs/dust/cms/user/albrecha/uhh2_102X_v2/HOTVRStudiesOutput/HOTVR_ML/ttbar_constituents_VR_08_04.csv"

fFile = TFile("/nfs/dust/cms/user/albrecha/uhh2_102X_v2/HOTVRStudiesOutput/HOTVR_ML/uhh2.AnalysisModuleRunner.MC.ttbar_pythia8_flat_nnpdf23.root", "READ")
#fFile = TFile("/nfs/dust/cms/user/albrecha/uhh2_102X_v2/HOTVRStudiesOutput/HOTVR_ML/uhh2.AnalysisModuleRunner.MC.QCD_flat_prod1.root", "READ")

fTree = fFile.Get("AnalysisTree")

ievent = 0
with open(csv_ttbar, 'w') as csvfile:
    writer = csv.writer(csvfile, delimiter=',')
    while ievent<nevents_max:## loop over events
        jets = fTree.GetEntry(ievent)
        jets_px = fTree.jet_info_px
        jets_py = fTree.jet_info_py
        jets_pz = fTree.jet_info_pz
        jets_m = fTree.jet_info_m
        #print('event ')
        #print(ievent)
        #print('jet length ')
        #print(len(jets_px))
        for j in range(0, len(jets_px)): # loop over jets
            constituents_px = jets_px[j]
            constituents_py = jets_py[j]
            constituents_pz = jets_pz[j]
            constituents_m = jets_m[j]
            ## save in csv file
            writer.writerow(['jet','','',''])
            #print('constituents length ')
            #print(len(constituents_px))
            for k in range(0, len(constituents_px)): #loop over constituents
                px = constituents_px[k]
                py = constituents_py[k]
                pz = constituents_pz[k]
                m = constituents_m[k]
                writer.writerow([px, py, pz, m]) ## write one row (info of constituents, should be a vector)
            #end constituents
        #end jets
        ievent += 1
    # end open
