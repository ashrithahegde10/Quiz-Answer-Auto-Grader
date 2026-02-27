#include "quizgrader.h"
#include <time.h>

void printJSON(char questions[][MAX_LINE], char studAns[][MAX_LINE], int qCount) {
    printf("Content-Type: application/json\n\n");
    printf("{\n");
    printf("  \"results\": [\n");
    
    float totalScore = 0;
    
    for (int i = 0; i < qCount; i++) {
        char *modelAnswer = searchHash(questions[i]);
        if (modelAnswer) {
            float score = matchScoreUsingTrie(modelAnswer, studAns[i]);
            totalScore += score;
            
            printf("    {\n");
            printf("      \"question\": \"%s\",\n", questions[i]);
            printf("      \"modelAnswer\": \"%s\",\n", modelAnswer);
            printf("      \"studentAnswer\": \"%s\",\n", studAns[i]);
            printf("      \"score\": %.4f,\n", score);
            printf("      \"percentage\": %.2f\n", score * 100);
            printf("    }%s\n", (i < qCount - 1) ? "," : "");
        }
    }
    
    float avgScore = (totalScore / qCount) * 100;
    printf("  ],\n");
    printf("  \"totalQuestions\": %d,\n", qCount);
    printf("  \"totalScore\": %.2f,\n", totalScore);
    printf("  \"percentage\": %.2f\n", avgScore);
    printf("}\n");
}

int main() {
    FILE *modelFile = fopen("quiz.csv", "r");
    FILE *studentFile = fopen("student_answers.csv", "r");

    if (!modelFile || !studentFile) {
        printf("Content-Type: application/json\n\n");
        printf("{\"error\": \"Could not open CSV files\"}\n");
        return 1;
    }

    char line[MAX_LINE];
    char questions[MAX_Q][MAX_LINE], studAns[MAX_Q][MAX_LINE];
    int qCount = 0;

    fgets(line, sizeof(line), modelFile);
    fgets(line, sizeof(line), studentFile);

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

    printJSON(questions, studAns, qCount);

    return 0;
}