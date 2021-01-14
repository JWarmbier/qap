//
// Created by jwarmbier on 04/11/2020.
//

#ifndef QAP_QAPEXCEPTION_H
#define QAP_QAPEXCEPTION_H
#include <exception>

class QAPLoadDataError: public std::exception
{
    virtual const char* what() const throw()
    {
        return "Load Data Error: Input file does not exist";
    }
};



class QAPDataFileError: public std::exception{

    virtual const char* what() const throw()
    {
        return "Data File Error: Data in file is not consistent with the standard.";
    }
};

class QAPSolutionError : public std::exception{
    virtual const char* what() const throw(){
        return "Load Solution Error: Input file does not exist";
    }
};

class QAPSolutionSizeError : public std::exception{
    virtual const char* what() const throw(){
        return "Load Solution Error: Size of solution is inconsistent";
    }
};

#endif //QAP_QAPEXCEPTION_H