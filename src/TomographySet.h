#ifndef TOMOGRAPHY_SET_H
#define TOMOGRAPHY_SET_H

/**
 * @brief Define a Tomography for a single row or column
 *
 */
typedef struct Tomography {
    int size;
    int *tuple;
} Tomography;

class TomographySet {
    private:
        int width;
        int height;
        Tomography *row;
        Tomography *col;
    
    public:
        TomographySet(int width, int height);
        TomographySet(const char *file);

        ~TomographySet();

        int getWidth();
        int getHeight();

        void save(const char *file);
        
        Tomography getRowTomography(int row);
        Tomography getColTomography(int col);

        int maxColSize();
        int maxRowSize();

        int charRowWidth();
        int charColWidth();

        char ***colFormatArray(int *arrW, int *arrH, int *numChar);
        char ***rowFormatArray(int *arrW, int *arrH, int *numChar);

};

#endif