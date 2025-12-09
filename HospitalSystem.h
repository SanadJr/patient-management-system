// بسم الله الرحمن الرحيم
// "وَأَنْ لَيْسَ لِلْإِنسَانِ إِلَّا مَا سَعَىٰ"
// Free Palestine
#ifndef HOSPITALSYSTEM_H
#define HOSPITALSYSTEM_H

#include <iostream>
#include <map>
#include <string>
#include "Patient.h"
#include "PatientQueue.h"
#include "Doctor.h"
#include "DoctorList.h"


using namespace std;

class HospitalSystem
{
private:
    map<CaseType, DoctorList *> doctorsByMajor;
    PatientQueue patientQueue;

public:
    HospitalSystem();
    ~HospitalSystem();

    void run();

    // --- Patient Management ---
    void addPatient();
    void deletePatient();
    void showWaitingRoom();

    // --- Doctor Management ---
    void addDoctor();
    void showDoctors();

    // --- Core Workflow ---
    void assignPatient();
    void treatPatient();

    // --- Helper ---
    void printMainMenu();
};

#endif