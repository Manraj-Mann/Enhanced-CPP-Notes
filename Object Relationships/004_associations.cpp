#include <iostream>

/*

    Notes : Association

    1. Association : To qualify as an association, an object and another object must have the following relationship:

            - The associated object (member) is otherwise unrelated to the object (class)
            - The associated object (member) can belong to more than one object (class) at a time
            - The associated object (member) does not have its existence managed by the object (class)
            - The associated object (member) may or may not know about the existence of the object (class)

        - Unlike a composition or aggregation, where the part is a part of the whole object, in an association, the associated object is otherwise unrelated to the object. Just like an aggregation, the associated object can belong to multiple objects simultaneously, and isn’t managed by those objects. However, unlike an aggregation, where the relationship is always unidirectional, in an association, the relationship may be unidirectional or bidirectional (where the two objects are aware of each other).

        - The relationship between doctors and patients is a great example of an association. The doctor clearly has a relationship with his patients, but conceptually it’s not a part/whole (object composition) relationship. A doctor can see many patients in a day, and a patient can see many doctors (perhaps they want a second opinion, or they are visiting different types of doctors). Neither of the object’s lifespans are tied to the other.

        - We can say that association models as “uses-a” relationship. The doctor “uses” the patient (to earn income). The patient uses the doctor (for whatever health purposes they need).

    2. Implementing associations : Because associations are a broad type of relationship, they can be implemented in many different ways. However, most often, associations are implemented using pointers, where the object points at the associated object.

        - In this example, we’ll implement a bi-directional Doctor/Patient relationship, since it makes sense for the Doctors to know who their Patients are, and vice-versa.

            // Since Doctor and Patient have a circular dependency, we're going to forward declare Patient
            class Patient;

            class Doctor
            {
            private:
                std::string m_name{};
                std::vector<std::reference_wrapper<const Patient>> m_patient{};

            public:
                Doctor(std::string_view name) :
                    m_name{ name }
                {
                }

                void addPatient(Patient& patient);

                // We'll implement this function below Patient since we need Patient to be defined at that point
                friend std::ostream& operator<<(std::ostream& out, const Doctor& doctor);

                const std::string& getName() const { return m_name; }
            };

            class Patient
            {
            private:
                std::string m_name{};
                std::vector<std::reference_wrapper<const Doctor>> m_doctor{}; // so that we can use it here

                // We're going to make addDoctor private because we don't want the public to use it.
                // They should use Doctor::addPatient() instead, which is publicly exposed
                void addDoctor(const Doctor& doctor)
                {
                    m_doctor.push_back(doctor);
                }

            public:
                Patient(std::string_view name)
                    : m_name{ name }
                {
                }

                // We'll implement this function below to parallel operator<<(std::ostream&, const Doctor&)
                friend std::ostream& operator<<(std::ostream& out, const Patient& patient);

                const std::string& getName() const { return m_name; }

                // We'll friend Doctor::addPatient() so it can access the private function Patient::addDoctor()
                friend void Doctor::addPatient(Patient& patient);
            };

            void Doctor::addPatient(Patient& patient)
            {
                // Our doctor will add this patient
                m_patient.push_back(patient);

                // and the patient will also add this doctor
                patient.addDoctor(*this);
            }

            std::ostream& operator<<(std::ostream& out, const Doctor& doctor)
            {
                if (doctor.m_patient.empty())
                {
                    out << doctor.m_name << " has no patients right now";
                    return out;
                }

                out << doctor.m_name << " is seeing patients: ";
                for (const auto& patient : doctor.m_patient)
                    out << patient.get().getName() << ' ';

                return out;
            }

            std::ostream& operator<<(std::ostream& out, const Patient& patient)
            {
                if (patient.m_doctor.empty())
                {
                    out << patient.getName() << " has no doctors right now";
                    return out;
                }

                out << patient.m_name << " is seeing doctors: ";
                for (const auto& doctor : patient.m_doctor)
                    out << doctor.get().getName() << ' ';

                return out;
            }

            int main()
            {
                // Create a Patient outside the scope of the Doctor
                Patient dave{ "Dave" };
                Patient frank{ "Frank" };
                Patient betsy{ "Betsy" };

                Doctor james{ "James" };
                Doctor scott{ "Scott" };

                james.addPatient(dave);

                scott.addPatient(dave);
                scott.addPatient(betsy);

                std::cout << james << '\n';
                std::cout << scott << '\n';
                std::cout << dave << '\n';
                std::cout << frank << '\n';
                std::cout << betsy << '\n';

                return 0;
            }

        - 

    3. Reflexive association : Sometimes objects may have a relationship with other objects of the same type. This is called a reflexive association. A good example of a reflexive association is the relationship between a university course and its prerequisites (which are also university courses).

        class Course
        {
        private:
            std::string m_name{};
            const Course* m_prerequisite{};

        public:
            Course(std::string_view name, const Course* prerequisite = nullptr):
                m_name{ name }, m_prerequisite{ prerequisite }
            {
            }

        };

    4. Associations can be indirect : In all of the previous cases, we’ve used either pointers or references to directly link objects together. However, in an association, this is not strictly required. Any kind of data that allows you to link two objects together suffices. In the following example, we show how a Driver class can have a unidirectional association with a Car without actually including a Car pointer or reference member:

            class Car
            {
            private:
                std::string m_name{};
                int m_id{};

            public:
                Car(std::string_view name, int id)
                    : m_name{ name }, m_id{ id }
                {
                }

                const std::string& getName() const { return m_name; }
                int getId() const { return m_id; }
            };

            // Our CarLot is essentially just a static array of Cars and a lookup function to retrieve them.
            // Because it's static, we don't need to allocate an object of type CarLot to use it
            namespace CarLot
            {
                Car carLot[4] { { "Prius", 4 }, { "Corolla", 17 }, { "Accord", 84 }, { "Matrix", 62 } };

                Car* getCar(int id)
                {
                    for (auto& car : carLot)
                    {
                        if (car.getId() == id)
                        {
                            return &car;
                        }
                    }

                    return nullptr;
                }
            };

            class Driver
            {
            private:
                std::string m_name{};
                int m_carId{}; // we're associated with the Car by ID rather than pointer

            public:
                Driver(std::string_view name, int carId)
                    : m_name{ name }, m_carId{ carId }
                {
                }

                const std::string& getName() const { return m_name; }
                int getCarId() const { return m_carId; }
            };

            int main()
            {
                Driver d{ "Franz", 17 }; // Franz is driving the car with ID 17

                Car* car{ CarLot::getCar(d.getCarId()) }; // Get that car from the car lot

                if (car)
                    std::cout << d.getName() << " is driving a " << car->getName() << '\n';
                else
                    std::cout << d.getName() << " couldn't find his car\n";

                return 0;
            }

        - In this particular example, doing things this way is kind of silly, since getting the Car out of the CarLot requires an inefficient lookup (a pointer connecting the two is much faster). However, there are advantages to referencing things by a unique ID instead of a pointer. For example, you can reference things that are not currently in memory (maybe they’re in a file, or in a database, and can be loaded on demand). Also, pointers can take 4 or 8 bytes -- if space is at a premium and the number of unique objects is fairly low, referencing them by an 8-bit or 16-bit integer can save lots of memory.

    5. Composition vs aggregation vs association summary : Here’s a summary table to help you remember the difference between composition, aggregation, and association:

        Property	                                    Composition	| Aggregation	| Association
        ----------------------------------------------------------------------------------------------------------
        Relationship type	                             Whole/part	|    Whole/part	| Otherwise unrelated
        Members can belong to multiple classes	             No	    |    Yes	    |   Yes
        Members’ existence managed by class	                 Yes	|       No	    |   No
        Directionality	                             Unidirectional	| Unidirectional| Unidirectional or bidirectional
        Relationship verb	                                Part-of	|    Has-a	    |  Uses-a


*/
int main()
{
    return 0;
}