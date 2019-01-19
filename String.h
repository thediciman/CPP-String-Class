#ifndef H_STRING
#define H_STRING

#include <iostream>
#include <string.h>

using namespace std;

class String {
    // overloads stream insertion and extraction operators for Strings
    friend ostream& operator<< ( ostream&, const String& );
    friend istream& operator>> ( istream&, String& );
    friend istream& getline ( istream&, String&, const char& = '\n' );

    // overloads + operator for String concatenation
    friend String operator+ ( const String&, const String& );
    friend String operator+ ( const String&, const char* );
    friend String operator+ ( const char*, const String& );
    friend String operator+ ( const String&, const char& );
    friend String operator+ ( const char&, const String& );

    // overloads comparison operators for Strings
    friend bool operator== (const String&, const String& );
    friend bool operator!= (const String&, const String& );
    friend bool operator<  (const String&, const String& );
    friend bool operator<= (const String&, const String& );
    friend bool operator>  (const String&, const String& );
    friend bool operator>= (const String&, const String& );

public:
    static const size_t npos;     // greatest possible value for size_t
    static const size_t INIT_CAP; // initial capacity of a String

    // constructors for the String class
    String ( );
    String ( const String& );
    String ( const String&, const size_t&, const size_t& = npos );
    String ( const char*, const size_t& );
    String ( const char* );
    String ( const size_t&, const char& );

    ~String ( ); // destructor for the String class

    // overloads assignment operator for Strings
    String& operator= ( const String& );
    String& operator= ( const char* );
    String& operator= ( const char& );

    // overloads += operator for Strings
    String& operator+= ( const String& );
    String& operator+= ( const char* );
    String& operator+= ( const char& );

    // returns total number of characters in a String,
    // excluding the NULL character at the end
    size_t length ( ) const;
    size_t size ( ) const;

    // returns total number of characters that a String can hold
    size_t capacity ( ) const;

    bool empty ( ) const; // tests whether a String is empty
    void clear ( );       // erases all characters of a String

    // inserts a character at the end of a String
    void push_back ( const char& );

    // overloads subscription operator for Strings
    char& operator[] ( const size_t& );
    const char& operator[] ( const size_t& ) const;

    // returns the character in an index position with
    // out_of_range error checking
    char& at ( const size_t& );
    const char& at ( const size_t& ) const;

    // returns the sub-String that starts in an index position
    // for a given size
    String substr ( const size_t& = 0, const size_t& = npos );

    // converts a String to a C-string
    const char* c_str ( ) const;
    const char* data ( ) const;

private:
    // number of characters in a String, excluding the NULL
    // character at the end
    size_t sz;

    // allocated memory capacity for a String
    size_t cap;

    // points to the buffer space that stores a String
    char* p;

    // expands the buffer memory for a given size
    void expandMem ( const size_t& );
};

#endif
