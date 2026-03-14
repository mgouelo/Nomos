#ifndef STUDENTDAO_H
#define STUDENTDAO_H

#include <QList>
#include "src/dto/Student.h"

class StudentDao {
public :
    StudentDao();

    // Insert a new student
    bool insertStudent(const Student& student);

    // Get all students
    QList<Student> getAllStudents() const;

    // Clear the table
    bool deleteAllStudents();
};

#endif // STUDENTDAO_H
