#include <iostream>
#include <fstream>

#include "io.h"

using namespace std;
using namespace Cantera;

namespace HeteroCt
{

void print_formation_enthalpy(vector<ThermoPhase*> phases, string output_file) 
{
    vector<doublereal> hform; 
    ofstream out;
    out.open(output_file);
    out << "#Dimensionless formation enthalpies of species (H/RT)\n" << endl;
    for  (const auto phase: phases){
        hform.resize(phase->nSpecies());
        phase->getEnthalpy_RT(hform.data());
        for (size_t k = 0; k < phase->nSpecies(); k++) {
            out.width(12); 
            out << std::left << phase->speciesName(k); 
            out.width(12); 
            out << std::right << hform[k] << endl;
        }   
    }   
    out.close();
}

void print_formation_entropy(vector<ThermoPhase*> phases, string output_file) 
{
    vector<doublereal> sform; 
    ofstream out;
    out.open(output_file);
    out << "#Dimensionless formation entropies of species (S/R)\n" << endl;
    for  (const auto phase: phases){
        sform.resize(phase->nSpecies());
        phase->getEntropy_R(sform.data());
        for (size_t k = 0; k < phase->nSpecies(); k++) {
            out.width(12); 
            out << std::left << phase->speciesName(k); 
            out.width(12); 
            out << std::right << sform[k] << endl;
        }   
    }   
    out.close();
}


void print_rxn_enthalpy(vector<Kinetics*> kinetic_mgrs, doublereal T, string output_file)
{
    vector<doublereal> hrxn;
    ofstream out;
    out.open(output_file);
    out << "#Dimensionless enthalpies of reactions (H/RT)\n" << endl;
    for  (const auto mgr: kinetic_mgrs){
        size_t size = mgr->nReactions();
        if (size > 0) {
            hrxn.resize(size);
            mgr->getDeltaEnthalpy(hrxn.data());
            for (size_t k = 0; k < size; k++) {
                out.width(12);
                out << std::left << hrxn[k]/(GasConstant*T) ;
                out.width(12);
                out << std::left << mgr->reactionString(k) << endl;
            }
        }
    }
    out.close();
}

void print_rxn_entropy(vector<Kinetics*> kinetic_mgrs, string output_file)
{
    vector<doublereal> sRxn;
    ofstream out;
    out.open(output_file);
    out << "#Dimensionless entropies of reactions (S/R)\n" << endl;
    for  (const auto mgr: kinetic_mgrs){
        size_t size = mgr->nReactions();
        if (size > 0) {
            sRxn.resize(size);
            mgr->getDeltaSSEntropy(sRxn.data());
            for (size_t k = 0; k < size; k++) {
                out.width(12);
                out << std::left << sRxn[k]/GasConstant ;
                out.width(12);
                out << std::left << mgr->reactionString(k) << endl;
            }
        }
    }
    out.close();
}


void print_rxn_eq_consts(vector<Kinetics*> kinetic_mgrs, string output_file)
{
    vector<doublereal> kc;
    ofstream out;
    out.open(output_file);
    out << "#Equilibrium constants of reactions\n" << endl;
    for  (const auto mgr: kinetic_mgrs){
        size_t size = mgr->nReactions();
        if (size > 0) {
            kc.resize(size);
            mgr->getEquilibriumConstants(kc.data());
            for (size_t k = 0; k < size; k++) {
                out.width(12);
                out << std::left << kc[k];
                out.width(12);
                out << std::left << mgr->reactionString(k) << endl;
            }
        }
    }
    out.close();
}

void print_rxn_gibbs(vector<Kinetics*> kinetic_mgrs, doublereal T,  
        string output_file)
{
    vector<doublereal> muRxn; 
    ofstream out;
    out.open(output_file);
    out << "#Dimensionless Gibbs Energies of reactions (G/RT)\n" << endl;
    for  (const auto mgr: kinetic_mgrs){
        size_t size = mgr->nReactions();
        if (size > 0) {
            muRxn.resize(size);
            mgr->getDeltaSSGibbs(muRxn.data());
            for (size_t k = 0; k < size; k++) {
                out.width(12); 
                out << std::left << muRxn[k]/(GasConstant*T) ;
                out.width(12); 
                out << std::left << mgr->reactionString(k) << endl;
            }
        }
    }
    out.close();
}


void print_rxn_kc(vector<Kinetics*> kinetic_mgrs, string output_file)
{
    vector<doublereal> kc; 
    ofstream out;
    out.open(output_file);
    out << "#Equilibrium constants of reactions\n" << endl;
    for  (const auto mgr: kinetic_mgrs){
        size_t size = mgr->nReactions();
        if (size > 0) {
            kc.resize(size);
            mgr->getEquilibriumConstants(kc.data());
            for (size_t k = 0; k < size; k++) {
                out.width(12); 
                out << std::left << kc[k];
                out.width(12); 
                out << std::left << mgr->reactionString(k) << endl;
            }
        }
    }
    out.close();
}

void print_rxn_kf(vector<Kinetics*> kinetic_mgrs, string output_file)
{
    vector<doublereal> kf; 
    ofstream out;
    out.open(output_file);
    out << "#Forward rate constants of reactions\n" << endl;
    for  (const auto mgr: kinetic_mgrs){
        size_t size = mgr->nReactions();
        if (size > 0) {
            kf.resize(size);
            mgr->getFwdRateConstants(kf.data());
            for (size_t k = 0; k < size; k++) {
                out.width(12); 
                out << std::left << kf[k];
                out.width(12); 
                out << std::left << mgr->reactionString(k) << endl;
            }
        }
    }
    out.close();
}

void print_rxn_kr(vector<Kinetics*> kinetic_mgrs, string output_file)
{
    vector<doublereal> kr; 
    ofstream out;
    out.open(output_file);
    out << "#Reverse rate constants of reactions\n" << endl;
    for  (const auto mgr: kinetic_mgrs){
        size_t size = mgr->nReactions();
        if (size > 0) {
            kr.resize(size);
            mgr->getRevRateConstants(kr.data());
            for (size_t k = 0; k < size; k++) {
                out.width(12); 
                out << std::left << kr[k];
                out.width(12); 
                out << std::left << mgr->reactionString(k) << endl;
            }
        }
    }
    out.close();
}

void print_htrct_header(std::ofstream& out) {
    out << "-----------------------------------------------------------\n" 
        << "Hetero_ct: version 0.0.1\n" 
        << "-----------------------------------------------------------\n\n" 
        << "Hetero_ct is a multiphysics and multiscale software aimed at" << std::endl
        << "modelng chemical kinetics for heterogeneous catalysis." << std::endl
        << "Hetero_ct is open source and is developed at Delaware Energy" << std::endl
        << "Institute, Unitversity of Delaware. Hetero_ct uses Cantera," << std::endl
        << "an open source software available at www.cantera.org, as backend.\n\n\n"; 
}

}