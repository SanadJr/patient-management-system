// بسم الله الرحمن الرحيم
// "وَأَنْ لَيْسَ لِلْإِنسَانِ إِلَّا مَا سَعَىٰ"
// Free Palestine
#include "HospitalSystem.h"

// ================= CONSTRUCTOR & DESTRUCTOR =================

HospitalSystem::HospitalSystem()
{
    doctorsByMajor[GENERAL] = new DoctorList();
    doctorsByMajor[EMERGENCY] = new DoctorList();
    doctorsByMajor[ICU] = new DoctorList();
    doctorsByMajor[PEDIATRIC] = new DoctorList();
    doctorsByMajor[SURGICAL] = new DoctorList();
}

HospitalSystem::~HospitalSystem()
{
    cout << "System shutting down... Cleaning up memory." << endl;
    for (auto const &[key, listPtr] : doctorsByMajor)
    {
        delete listPtr;
    }
}

// ================= PATIENT MANAGEMENT =================

void HospitalSystem::addPatient()
{
    cout << "\n=== REGISTER NEW PATIENT ===" << endl;

    int id;
    cout << "Enter ID: ";
    cin >> id;

    string name;
    cout << "Enter Name: ";
    cin.ignore(); // Clears the "Enter" key from the buffer
    getline(cin, name);

    int age;
    cout << "Enter Age: ";
    cin >> age;

    int type;
    cout << "Select Case Type:\n0:General, 1:Emergency, 2:ICU, 3:Pediatric, 4:Surgical\nChoice: ";
    cin >> type;

    Patient p(id, name, age, (CaseType)type);
    patientQueue.enqueue(p);

    cout << "Success: Patient " << name << " added to Waiting Room." << endl;
}

void HospitalSystem::deletePatient()
{
    if (patientQueue.isEmpty())
    {
        cout << "Waiting room is empty." << endl;
        return;
    }

    int id;
    cout << "Enter Patient ID to remove from Waiting Room: ";
    cin >> id;

    Patient p = patientQueue.removeById(id);

    if (p.getId() != 0)
    {
        cout << "Patient " << p.getName() << " removed successfully." << endl;
    }
}

void HospitalSystem::showWaitingRoom()
{
    cout << "\n=== WAITING ROOM STATUS ===" << endl;
    patientQueue.display();
}

// ================= DOCTOR MANAGEMENT =================

void HospitalSystem::addDoctor()
{
    cout << "\n=== HIRE NEW DOCTOR ===" << endl;

    int id;
    cout << "Enter ID: ";
    cin >> id;

    string name;
    cout << "Enter Name: ";
    cin.ignore();
    getline(cin, name);

    int age;
    cout << "Enter Age: ";
    cin >> age;

    int type;
    cout << "Select Specialization:\n0:General, 1:Emergency, 2:ICU, 3:Pediatric, 4:Surgical\nChoice: ";
    cin >> type;

    CaseType major = (CaseType)type;
    Doctor d(id, name, age, major);

    doctorsByMajor[major]->addDoctor(d);
    cout << "Doctor " << name << " assigned to " << type << " department." << endl;
}

void HospitalSystem::showDoctors()
{
    int type;
    cout << "Select Department to View:\n0:General, 1:Emergency, 2:ICU, 3:Pediatric, 4:Surgical\nChoice: ";
    cin >> type;

    cout << "\n--- DOCTOR LIST (" << type << ") ---" << endl;
    doctorsByMajor[(CaseType)type]->display();
}

// ================= CORE WORKFLOW =================

void HospitalSystem::assignPatient()
{
    if (patientQueue.isEmpty())
    {
        cout << "No patients in the waiting room." << endl;
        return;
    }

    Patient nextP = patientQueue.next();
    CaseType neededMajor = nextP.getCaseType();

    cout << "\n=== ASSIGN PATIENT TO DOCTOR ===" << endl;
    cout << "Patient: " << nextP.getName() << " (Needs Dept: " << neededMajor << ")" << endl;

    DoctorList *deptList = doctorsByMajor[neededMajor];

    if (deptList->isEmpty())
    {
        cout << "CRITICAL: No doctors available in this department!" << endl;
        return;
    }

    cout << "Available Doctors in this Department:" << endl;
    deptList->display();

    int docId;
    cout << "Enter Doctor ID to assign: ";
    cin >> docId;

    PatientQueue *docQueue = deptList->SearchById(docId);

    if (docQueue != nullptr)
    {
        Patient p = patientQueue.dequeue();
        docQueue->enqueue(p);
        cout << "Success: Patient transferred to Dr. ID " << docId << endl;
    }
    else
    {
        cout << "Error: Invalid Doctor ID." << endl;
    }
}

void HospitalSystem::treatPatient()
{
    cout << "\n=== DOCTOR TREATMENT PORTAL ===" << endl;

    int type;
    cout << "Select Department:\n0:General, 1:Emergency, 2:ICU, 3:Pediatric, 4:Surgical\nChoice: ";
    cin >> type;

    DoctorList *list = doctorsByMajor[(CaseType)type];

    if (list->isEmpty())
    {
        cout << "No doctors in this department." << endl;
        return;
    }

    list->display();

    int docId;
    cout << "Enter Doctor ID performing the treatment: ";
    cin >> docId;

    list->treatPatient(docId);
}

// ================= MAIN MENU LOOP =================

void HospitalSystem::printMainMenu()
{
    cout << "\n==========================================" << endl;
    cout << "           HOSPITAL MANAGEMENT SYSTEM     " << endl;
    cout << "==========================================" << endl;
    cout << " 1. Register Patient (Add to Waiting Room)" << endl;
    cout << " 2. Hire Doctor" << endl;
    cout << " 3. ASSIGN Patient (Waiting Room -> Doctor)" << endl;
    cout << " 4. TREAT Patient (Discharge)" << endl;
    cout << " 5. View Waiting Room" << endl;
    cout << " 6. View Doctors by Department" << endl;
    cout << " 7. Delete Patient (From Waiting Room)" << endl;
    cout << " 0. Exit" << endl;
    cout << "==========================================" << endl;
    cout << " Select Option: ";
}

void HospitalSystem::run()
{
    int choice;
    while (true)
    {
        printMainMenu();
        cin >> choice;

        switch (choice)
        {
        case 1:
            addPatient();
            break;
        case 2:
            addDoctor();
            break;
        case 3:
            assignPatient();
            break;
        case 4:
            treatPatient();
            break;
        case 5:
            showWaitingRoom();
            break;
        case 6:
            showDoctors();
            break;
        case 7:
            deletePatient();
            break;
        case 0:
            return;
        default:
            cout << "Invalid option." << endl;
        }
    }
}