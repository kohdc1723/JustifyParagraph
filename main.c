#include <stdio.h>
#include <conio.h>
#define MAX_NUMBER_OF_WORDS 85
#define MAX_WORD_LENGTH 18

// justify the paragraph and print according to the format
void justifyAndPrintParagraph(char *paragraph, int lineLength);

// break down the paragraph into words and store them in the 2D array
int breakDownParagraphAndGetTotalWords(char *paragraph, char words[MAX_NUMBER_OF_WORDS][MAX_WORD_LENGTH]);

// get the length of the string
int getLength(char *inputString);

// return the number of words that need to be printed in the next line
int getNumberOfWordsForNextLine(char words[MAX_NUMBER_OF_WORDS][MAX_WORD_LENGTH], int lineLength, int processedWords);

// return the number of chars contained in the next line
int getNumberOfCharsForNextLine(char words[MAX_NUMBER_OF_WORDS][MAX_WORD_LENGTH], int wordsForNextLine, int processedWords);

// calculate the spaces between words and print out the paragraph
void printNextLine(char words[MAX_NUMBER_OF_WORDS][MAX_WORD_LENGTH], int processedWords, int wordsForNextLine, int charsForNextLine, int lineLength);

// print function when the line contains only one word
void printLineWithOneWord(char words[MAX_NUMBER_OF_WORDS][MAX_WORD_LENGTH], int processedWords, int charsForNextLine, int lineLength);

// print space
void printSpace(int num);

// main function
int main() {
    // case 1
    char paragraph1[] = "Prepare for a career in tech by joining GitHub Global Campus.";
    int lineLength1 = 30;
    printf("[ Paragraph: \"%s\" / Line Length: %d ]\n\n", paragraph1, lineLength1);
    justifyAndPrintParagraph(paragraph1, lineLength1);
    printf("\n");

    // case 2
    char paragraph2[] = "Problems arise occasionally when the following word begins with a vowel letter but actually starts with a consonant sound, or vice versa.";
    int lineLength2 = 40;
    printf("[ Paragraph: \"%s\" / Line Length: %d ]\n\n", paragraph2, lineLength2);
    justifyAndPrintParagraph(paragraph2, lineLength2);
    printf("\n");

    // case 3
    char paragraph3[] = "The British Columbia Institute of Technology, is a public polytechnic institute in Burnaby, British Columbia.";
    int lineLength3 = 50;
    printf("[ Paragraph: \"%s\" / Line Length: %d ]\n\n", paragraph3, lineLength3);
    justifyAndPrintParagraph(paragraph3, lineLength3);
    printf("\n");

    getch();
    return 0;
}

// justify the paragraph and print according to the format
void justifyAndPrintParagraph(char *paragraph, int lineLength) {
    char words[MAX_NUMBER_OF_WORDS][MAX_WORD_LENGTH] = {'\0'};
    int totalWords = breakDownParagraphAndGetTotalWords(paragraph, words);
    int processedWords = 0;
    while (processedWords < totalWords) {
        int wordsForNextLine = getNumberOfWordsForNextLine(words, lineLength, processedWords);
        int charsForNextLine = getNumberOfCharsForNextLine(words, wordsForNextLine, processedWords);
        if (wordsForNextLine > 1) {
            printNextLine(words, processedWords, wordsForNextLine, charsForNextLine, lineLength);
        } else {
            printLineWithOneWord(words, processedWords, charsForNextLine, lineLength);
        }
        processedWords += wordsForNextLine;
    }
}

// break down the paragraph into words and store them in the 2D array
int breakDownParagraphAndGetTotalWords(char *paragraph, char words[MAX_NUMBER_OF_WORDS][MAX_WORD_LENGTH]) {
    int wordNum = 0;
    int charNum = 0;
    while (*paragraph != '\0') {
        if (*paragraph != ' ') {
            words[wordNum][charNum] = *paragraph;
            charNum++;
        } else {
            wordNum++;
            charNum = 0;
        }
        paragraph++;
    }
    words[wordNum][charNum] = *paragraph;
    return wordNum + 1;
}

// get the length of the string
int getLength(char *inputString) {
    int length = 0;
    while (*inputString != '\0') {
        length++;
        inputString++;
    }
    return length;
}

// return the number of words that need to be printed in the next line
int getNumberOfWordsForNextLine(char words[MAX_NUMBER_OF_WORDS][MAX_WORD_LENGTH], int lineLength, int processedWords) {
    int wordsNum = 0;
    int sum = 0;
    int i = 0;
    while (sum <= lineLength + 1) {
        sum += (getLength(words[processedWords + i]) + 1);
        wordsNum++;
        i++;
        if (sum < lineLength + 1 && *words[processedWords + i] == '\0') {
            return wordsNum;
        }
    }
    if (sum <= lineLength + 1) {
        return wordsNum;
    } else {
        return wordsNum - 1;
    }
}

// return the number of chars contained in the next line
int getNumberOfCharsForNextLine(char words[MAX_NUMBER_OF_WORDS][MAX_WORD_LENGTH], int wordsForNextLine, int processedWords) {
    int i;
    int charNum = 0;
    for (i = 0; i < wordsForNextLine; i++) {
        charNum += getLength(words[processedWords + i]);
    }
    return charNum;
}

// calculate the spaces between words and print out the paragraph
void printNextLine(char words[MAX_NUMBER_OF_WORDS][MAX_WORD_LENGTH], int processedWords, int wordsForNextLine, int charsForNextLine, int lineLength) {
    int spaceBetweenWords = (lineLength - charsForNextLine) / (wordsForNextLine - 1);
    int spaceLeft = (lineLength - charsForNextLine) % (wordsForNextLine - 1);
    int i;
    for (i = 0; i < wordsForNextLine; i++) {
        printf("%s", words[processedWords + i]);
        if (i < wordsForNextLine - 1) {
            printSpace(spaceBetweenWords);
        }
        if (i < spaceLeft) {
            printSpace(1);
        }
    }
    printf("\n");
}

// print function when the line contains only one word
void printLineWithOneWord(char words[MAX_NUMBER_OF_WORDS][MAX_WORD_LENGTH], int processedWords, int charsForNextLine, int lineLength) {
    printf("%s", words[processedWords]);
    printSpace(lineLength - charsForNextLine);
    printf("\n");
}

// print space
void printSpace(int num) {
    int i;
    for (i = 0; i < num; i++) {
        printf(" ");
    }
}
