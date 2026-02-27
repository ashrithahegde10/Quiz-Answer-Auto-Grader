#include "quizgrader.h"

int main() {
    FILE *modelFile = fopen("quiz.csv", "r");
    FILE *studentFile = fopen("student_answers.csv", "r");

    if (!modelFile || !studentFile) {
        printf("Error: Could not open one or both CSV files.\n");
        return 1;
    }

    char line[MAX_LINE];
    char questions[MAX_Q][MAX_LINE], studAns[MAX_Q][MAX_LINE];
    int qCount = 0;

    // Skip header lines
    fgets(line, sizeof(line), modelFile);
    fgets(line, sizeof(line), studentFile);

    // -------------------- READ MODEL ANSWERS --------------------
    while (fgets(line, sizeof(line), modelFile)) {
        trimNewline(line);
        char *q = strtok(line, ",");
        char *a = strtok(NULL, ",");
        if (q && a) {
            insertHash(q, a);
            strcpy(questions[qCount], q);
            qCount++;
        }
    }

    // -------------------- READ STUDENT ANSWERS --------------------
    int sCount = 0;
    while (fgets(line, sizeof(line), studentFile) && sCount < qCount) {
        trimNewline(line);
        char *q = strtok(line, ",");
        char *a = strtok(NULL, ",");
        if (q && a) {
            strcpy(studAns[sCount], a);
            sCount++;
        }
    }

    fclose(modelFile);
    fclose(studentFile);

    printf("\n===== QUIZ AUTO-GRADER (Arrays + HashMap + Trie) =====\n");

    float totalScore = 0;
    int excellent = 0, good = 0, average = 0, poor = 0;

    // -------------------- GRADING --------------------
    for (int i = 0; i < qCount; i++) {
        char *modelAnswer = searchHash(questions[i]);
        if (modelAnswer) {
            float score = matchScoreUsingTrie(modelAnswer, studAns[i]);
            totalScore += score;
            const char *feedback = generateFeedback(score);

            printf("\nQ%d: %s\n", i + 1, questions[i]);
            printf("Model Answer: %s\n", modelAnswer);
            printf("Student Answer: %s\n", studAns[i]);
            printf("→ Match Score: %.2f%%\n", score * 100);
            printf("→ Feedback: %s\n", feedback);

            if (score >= 0.9) excellent++;
            else if (score >= 0.7) good++;
            else if (score >= 0.5) average++;
            else poor++;
        }
    }

    // -------------------- REPORT STATS --------------------
    float avgScore = (totalScore / qCount) * 100;

    printf("\n=====================================\n");
    printf("Final Score: %.2f%%\n", avgScore);
    printf("=====================================\n");
 
    printf("\n============= REPORT STATS =============\n");
    printf("Excellent Answers : %d\n", excellent);
    printf("Good Answers      : %d\n", good);
    printf("Average Answers   : %d\n", average);
    printf("Poor Answers      : %d\n", poor);
    printf("Overall Average Score: %.2f%%\n", avgScore);
    printf("=======================================\n");

    return 0;
}

