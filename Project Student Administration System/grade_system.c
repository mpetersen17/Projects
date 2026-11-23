#include "grade_system.h"

int isValidGrade(float grade) {
    //Verify if the grade is valid
    if(grade >= MIN_GRADE && grade <= MAX_GRADE){
            return OPERATION_SUCCESS;
    }
    else {
        return OPERATION_INVALID_INPUT;
    }
}

/*
 * GRADING SCALE:
 * A: 90.0 and above
 * B: 80.0 to 89.9
 * C: 70.0 to 79.9
 * D: 60.0 to 69.9
 * F: Below 60.0
 * N: Negative input (no grades) 
 */

char getLetterGrade(float average) {
    //check the averages and return the correct letter grade
    if(average >= 90.0) return 'A';

    else if (average >= 80.0 && average < 90.0) return 'B';

    else if (average >= 70.0 && average < 80.0) return 'C';

    else if (average >= 60.0 && average < 70.0) return 'D';

    else if (average >= 0.0 && average < 60.0) return 'F'; 
    
    else return 'N';
}

int findStudentByID(int id) {
    //iterate for each id to find the correspond student ID
    for(int i = 0; i < studentCount; i++) {
        if(studentIDs[i] == id) {
            return i;
        }
    }
    //The ID was not found
    return OPERATION_NOT_FOUND;
}

float calculateStudentAverage(int studentIndex) {
    if(studentIndex < 0 || studentIndex >=studentCount) {
        return -1.0;
    }
    float total = 0.0;
    int count = 0;

    if(quizGrades[studentIndex] != GRADE_NOT_ENTERED){
        total += quizGrades[studentIndex];
        count++;
    }

    if(assignmentGrades[studentIndex] != GRADE_NOT_ENTERED) {
        total += assignmentGrades[studentIndex];
        count++;
    }
    
    if(midtermGrades[studentIndex] != GRADE_NOT_ENTERED) {
        total += midtermGrades[studentIndex];
        count++;
    }

    if(finalGrades[studentIndex] != GRADE_NOT_ENTERED) {
        total += finalGrades[studentIndex];
        count++;
    }

    if (count == 0) {
        return -1.0;
    }
    return total / count;
}

int addStudent(int studentID) {
    if (studentID < 1 || studentID > MAX_STUDENT_ID) {
        return OPERATION_INVALID_INPUT; // Invalid ID
    }

    if (findStudentByID(studentID) != OPERATION_NOT_FOUND) {
        return OPERATION_DUPLICATE_ERROR; // Duplicate student ID
    }

    if (studentCount >= MAX_STUDENTS) {
        return OPERATION_CAPACITY_ERROR; // Max capacity reached
    }

    studentIDs[studentCount] = studentID;
    quizGrades[studentCount] = GRADE_NOT_ENTERED;
    assignmentGrades[studentCount] = GRADE_NOT_ENTERED;
    midtermGrades[studentCount] = GRADE_NOT_ENTERED;
    finalGrades[studentCount] = GRADE_NOT_ENTERED;
    studentCount++;
    
    return OPERATION_SUCCESS; // Student added successfully
}

int enterGrade(int studentID, int assessmentType, float grade) {
    if (grade < MIN_GRADE || grade > MAX_GRADE) {
        return OPERATION_INVALID_INPUT; 
    }

    int studentIndex = findStudentByID(studentID);
    if (studentIndex == OPERATION_NOT_FOUND) {
        return OPERATION_NOT_FOUND; 
    }

    switch (assessmentType) {
        case ASSESSMENT_QUIZ:
            quizGrades[studentIndex] = grade;
            break;
        case ASSESSMENT_ASSIGNMENT:
            assignmentGrades[studentIndex] = grade;
            break;
        case ASSESSMENT_MIDTERM:
            midtermGrades[studentIndex] = grade;
            break;
        case ASSESSMENT_FINAL:
            finalGrades[studentIndex] = grade;
            break;
        default:
            return OPERATION_INVALID_INPUT;
    }

    return OPERATION_SUCCESS; 
}

int displayStudentGrades(int studentID) {
    // check if the student exist
    int studentIndex = findStudentByID(studentID);
    if (studentIndex == OPERATION_NOT_FOUND) {
        return OPERATION_NOT_FOUND; 
    }

    // print the student grades with his own grade letter
    printf("Grades for Student ID %d:\n", studentID);
    printf("  Quiz: %.2f (%c)\n", quizGrades[studentIndex], getLetterGrade(quizGrades[studentIndex]));
    printf("  Assignment: %.2f (%c)\n", assignmentGrades[studentIndex], getLetterGrade(assignmentGrades[studentIndex]));
    printf("  Midterm: %.2f (%c)\n", midtermGrades[studentIndex], getLetterGrade(midtermGrades[studentIndex]));
    printf("  Final: %.2f (%c)\n", finalGrades[studentIndex], getLetterGrade(finalGrades[studentIndex]));

    return OPERATION_SUCCESS; 

}

int calculateStatistics(void) {
    // Step 1: Initialize global arrays to default values
    for(int i = 0; i < 16; i++) {
        assessmentStats[i] = -1.0;  // -1 indicates no data available
    }
    for(int i = 0; i < 5; i++) {
        gradeDistributionCounts[i] = 0;
    }
    
    // Step 2: Check if students exist
    if(studentCount <= 0) {
        return OPERATION_NOT_FOUND;
    }

    float totalQuiz = 0.0, totalAssignment = 0.0, totalMidterm = 0.0, totalFinal = 0.0;
    int quizCount = 0, assignmentCount = 0, midtermCount = 0, finalCount = 0;
    float minQuiz = MAX_GRADE, maxQuiz = MIN_GRADE;
    float minAssignment = MAX_GRADE, maxAssignment = MIN_GRADE;
    float minMidterm = MAX_GRADE, maxMidterm = MIN_GRADE;
    float minFinal = MAX_GRADE, maxFinal = MIN_GRADE;

    // Calculate Quiz statistics
    for (int i = 0; i < studentCount; i++) {
        if (quizGrades[i] != GRADE_NOT_ENTERED) {
            totalQuiz += quizGrades[i];
            quizCount++;
            if (quizGrades[i] < minQuiz) minQuiz = quizGrades[i];
            if (quizGrades[i] > maxQuiz) maxQuiz = quizGrades[i];
        }
    }
    if (quizCount > 0) {
        assessmentStats[0] = totalQuiz / quizCount; // Average
        assessmentStats[1] = quizCount;            // Count
        assessmentStats[2] = minQuiz;              // Min
        assessmentStats[3] = maxQuiz;              // Max
    }

    // Calculate Assignment statistics
    for (int i = 0; i < studentCount; i++) {
        if (assignmentGrades[i] != GRADE_NOT_ENTERED) {
            totalAssignment += assignmentGrades[i];
            assignmentCount++;
            if (assignmentGrades[i] < minAssignment) minAssignment = assignmentGrades[i];
            if (assignmentGrades[i] > maxAssignment) maxAssignment = assignmentGrades[i];
        }
    }
    if (assignmentCount > 0) {
        assessmentStats[4] = totalAssignment / assignmentCount; // Average
        assessmentStats[5] = assignmentCount;                 // Count
        assessmentStats[6] = minAssignment;                   // Min
        assessmentStats[7] = maxAssignment;                   // Max
    }

    // Calculate Midterm statistics
    for (int i = 0; i < studentCount; i++) {
        if (midtermGrades[i] != GRADE_NOT_ENTERED) {
            totalMidterm += midtermGrades[i];
            midtermCount++;
            if (midtermGrades[i] < minMidterm) minMidterm = midtermGrades[i];
            if (midtermGrades[i] > maxMidterm) maxMidterm = midtermGrades[i];
        }
    }
    if (midtermCount > 0) {
        assessmentStats[8] = totalMidterm / midtermCount; // Average
        assessmentStats[9] = midtermCount;               // Count
        assessmentStats[10] = minMidterm;                // Min
        assessmentStats[11] = maxMidterm;                // Max
    }

    // Calculate Final statistics
    for (int i = 0; i < studentCount; i++) {
        if (finalGrades[i] != GRADE_NOT_ENTERED) {
            totalFinal += finalGrades[i];
            finalCount++;
            if (finalGrades[i] < minFinal) minFinal = finalGrades[i];
            if (finalGrades[i] > maxFinal) maxFinal = finalGrades[i];
        }
    }
    if (finalCount > 0) {
        assessmentStats[12] = totalFinal / finalCount; // Average
        assessmentStats[13] = finalCount;             // Count
        assessmentStats[14] = minFinal;               // Min
        assessmentStats[15] = maxFinal;               // Max
    }

    // Step 4: Calculate grade distribution (A, B, C, D, F counts)
    for (int i = 0; i < studentCount; i++) {
        float studentAverage = calculateStudentAverage(i);
        if(studentAverage == -1.0){
            continue;
        }
        // Convert to letter grade
        char grade = getLetterGrade(studentAverage);

        // Increment the appropriate grade distribution count
        switch (grade) {
            case 'A': gradeDistributionCounts[0]++; break;
            case 'B': gradeDistributionCounts[1]++; break;
            case 'C': gradeDistributionCounts[2]++; break;
            case 'D': gradeDistributionCounts[3]++; break;
            case 'F': gradeDistributionCounts[4]++; break;
        }
    }

    // Return success after calculation
    return OPERATION_SUCCESS;
}

