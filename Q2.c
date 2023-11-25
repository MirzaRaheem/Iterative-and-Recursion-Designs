#include <stdio.h>
#include <stdlib.h>

// Function to read PGM file and store pixel values in dynamic memory
int* readPGM(const char* filename, int* width, int* height);

// Function to write PGM file with histogram equalized pixel values in ASCII format
void writePGM_ASCII(const char* filename, int* pixelValues, int width, int height);

// Function to perform histogram equalization
void histogramEqualization(int* pixelValues, int width, int height);

int main() {
    const char* inputFilename = "Rain_Tree.pgm";
    const char* outputFilename = "Equalized_Rain_Tree_ASCII.pgm";

    int width, height;
    int* pixelValues = readPGM(inputFilename, &width, &height);

    if (pixelValues == NULL) {
        fprintf(stderr, "Error reading PGM file.\n");
        return 1;
    }

    histogramEqualization(pixelValues, width, height);

    writePGM_ASCII(outputFilename, pixelValues, width, height);

    // Free allocated memory
    free(pixelValues);

    return 0;
}

int* readPGM(const char* filename, int* width, int* height) {
    FILE* file = fopen(filename, "r");
    if (!file) {
        fprintf(stderr, "Error opening file: %s\n", filename);
        return NULL;
    }

    char format[3];
    fscanf(file, "%2s", format);

    if (format[0] != 'P' || format[1] != '2') {
        fprintf(stderr, "Invalid PGM file format.\n");
        fclose(file);
        return NULL;
    }

    // Skip any comments in the header
    char c = getc(file);
    while (c == '#') {
        while (getc(file) != '\n') ; // Skip the entire line
        c = getc(file);
    }
    ungetc(c, file); // Put back the character that is not '#'

    fscanf(file, "%d %d", width, height);

    int maxPixelValue;
    fscanf(file, "%d", &maxPixelValue);

    int* pixelValues = (int*)malloc((*width) * (*height) * sizeof(int));

    for (int i = 0; i < (*width) * (*height); ++i) {
        fscanf(file, "%d", &pixelValues[i]);
    }

    fclose(file);

    return pixelValues;
}

void writePGM_ASCII(const char* filename, int* pixelValues, int width, int height) {
    FILE* file = fopen(filename, "w");
    if (!file) {
        fprintf(stderr, "Error opening file: %s\n", filename);
        return;
    }

    fprintf(file, "P2\n%d %d\n255\n", width, height);

    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            fprintf(file, "%d ", pixelValues[i * width + j]);
        }
        fprintf(file, "\n");
    }

    fclose(file);
}

void histogramEqualization(int* pixelValues, int width, int height) {
    // Step 1: Compute histogram
    int* histogram = (int*)calloc(256, sizeof(int));
    for (int i = 0; i < width * height; ++i) {
        histogram[pixelValues[i]]++;
    }

    // Step 2: Calculate cumulative histogram
    int* cumulativeHist = (int*)malloc(256 * sizeof(int));
    cumulativeHist[0] = histogram[0];
    for (int i = 1; i < 256; ++i) {
        cumulativeHist[i] = cumulativeHist[i - 1] + histogram[i];
    }

    // Step 3: Image Mapping
    for (int i = 0; i < width * height; ++i) {
        pixelValues[i] = (cumulativeHist[pixelValues[i]] * 255) / (width * height);
    }

    // Free allocated memory
    free(histogram);
    free(cumulativeHist);
}
