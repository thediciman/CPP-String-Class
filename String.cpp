#include "String.h"

using namespace std;

// UNLIMITED SPACE!... jk. it's only max that an unsigned int can hold
const size_t String::npos = -1;

// initial capacity will be 1, for '\0' only
const size_t String::INIT_CAP = 22;

// overloads stream insertion and extraction operators for Strings
ostream& operator<<(ostream &os, const String &s) {
    // insert each character from p into the ostream
    for (size_t i = 0; i < s.sz; i++) {
        os << s.p[i];
        // if we get to a '\0', break out of the loop
        if(s.p[i] == '\0') {
            break;
        }
    }
    // return the stream
    return os;
}

istream& operator>>(istream &is, String &s) {
    // same as getline, i guess, from the description in the document
    return getline(is, s);
}

istream& getline(istream &is, String &s, const char &del) {
    char ch;
    // clear the string
    s.clear();
    // read all the characters from the istream till we reach the del or the istream ends
    while (is.get(ch) && ch != del) {
        s.push_back(ch);
    }
    // return the string
    return is;
}

// for concatenation we're just gonna use the overloaded operator+=
// much simpler, and it works
String operator+(const String& s1, const String& s2) {
    String a(s1);
    a += s2;
    return a;
}

String operator+(const String& s, const char* c) {
    String a(s);
    a += c;
    return a;
}

String operator+(const char* c, const String& s) {
    String a(c);
    a += s;
    return a;
}

String operator+(const String& s, const char& c) {
    String a(s);
    a += c;
    return a;
}

String operator+(const char& c, const String& s) {
    String a;
    a += c;
    a += s;
    return a;
}

// check if two strings are equal
bool operator==(const String &s1, const String &s2) {
    return strcmp(s1.p, s2.p) == 0;
}

// returns the opposite of ==
bool operator!=(const String& s1, const String& s2) {
    return !(s1 == s2);
}

// only implement this one, basically
bool operator< (const String& s1, const String& s2) {
    // s2 > s1 if strcmp(s1, s2) < 0
    return strcmp(s1.p, s2.p) < 0;
}

// strings are equal or s1 is less than s2
bool operator<=(const String& s1, const String& s2) {
    return (s1 == s2) || (s1 < s2);
}

// strings are not equal and s1 is not less than s2
bool operator> (const String& s1, const String& s2) {
    return (s1 != s2) && !(s1 < s2);
}

// strings are equal or s1 is bigger than s2
bool operator>=(const String& s1, const String& s2) {
    return (s1 == s2) || (s1 > s2);
}

// constructors for the String class
String::String() {
    cap = INIT_CAP;
    p = (char*) malloc(cap * sizeof(char));
    p[0] = '\0';
    // initial size = 0
    sz = 0;
}

String::String(const String &s) {
    cap = INIT_CAP;

    p = (char*) malloc(cap * sizeof(char));

    // set the size
    sz = s.sz;

    // if the size is bigger than the initial capacity, allocate enough memory
    // so that we can store s's content into the current string

    if (sz >= cap) {
        expandMem(cap);
    }

    // copy s's content into p
    strcpy(p, s.p);
}

String::String(const String &s, const size_t &pos, const size_t &n) {
    cap = INIT_CAP;

    p = (char*) malloc(cap * sizeof(char));

    // starting from position pos, add n characters from s
    // we need at least n characters in the char array
    sz = n;

    if (sz >= cap) {
        expandMem(cap);
    }

    // iterate through the String
    size_t i = 0;
    // if we finished the string, break the loop
    for (; (i < sz) && (i + pos < s.sz); i++) {
        p[i] = s.p[i + pos];
    }
    // set the '\0' to terminate the string
    p[i] = '\0';
}

String::String(const char *c, const size_t &n) {
    cap = INIT_CAP;

    p = (char*) malloc(cap * sizeof(char));

    // copy n characters from the "c" c-string
    // size will be n
    sz = n;

    if (sz >= cap) {
        expandMem(cap);
    }

    size_t i = 0;
    // if we finished the string, break out of the loop
    for(; (i < n) && (i < strlen(c)); i++) {
        p[i] = c[i];
    }

    // terminate the string
    p[i] = '\0';
}

String::String(const char *s) {
    cap = INIT_CAP;

    p = (char*) malloc(cap * sizeof(char));

    // simply copy the s into the p
    sz = strlen(s);

    if (sz >= cap) {
        expandMem(cap);
    }

    // copy s into p
    strcpy(p, s);
}

String::String(const size_t &t, const char &c) {
    cap = INIT_CAP;

    p = (char*) malloc(cap * sizeof(char));

    sz = t;
    if (sz >= cap) {
        expandMem(cap);
    }
    // fill it
    for (size_t i = 0; i < t; i++) {
        p[i] = c;
    }
    // terminate it
    p[sz] = '\0';
}

// destructor for the String class
String::~String() {
    // deallocate the memory from the buffer
    free(p);
}

// overloads assignment operator for Strings
String &String::operator=(const String& s) {
    // copy the size from s to the current String
    sz = s.sz;

    if (sz >= cap) {
        expandMem(cap);
    }

    // copy all the characters from s to this string
    for (size_t i = 0; i < sz; i++) {
        p[i] = s.p[i];
    }

    // terminate the string
    p[sz] = '\0';

    // return this string
    return *this;
}

String &String::operator=(const char* s) {
    // simply copy the s into the p
    sz = strlen(s);

    if (sz >= cap) {
        expandMem(cap);
    }

    // copy the content from s into p
    strcpy(p, s);

    return *this;
}

String &String::operator=(const char& c) {
    // assign a single character
    sz = 1;

    if (sz >= cap) {
        expandMem(cap);
    }

    // set the character and terminate the string
    p[0] = c;
    p[1] = '\0';
    return *this;
}

// overloads += operator for Strings
String &String::operator+=(const String& s) {
    sz += s.sz;

    // temp array for merging the two strings
    char *tmp = (char*) malloc((sz + 1) * sizeof(char));

    // copy p into t
    strcpy(tmp, p);

    // concat s.p with tmp
    strcat(tmp, s.p);

    if (sz >= cap) {
        expandMem(cap);
    }

    // copy tmp into p
    strcpy(p, tmp);

    // return
    return *this;
}

String &String::operator+=(const char* cs) {
    // concat a c-string to our current string
    String tmp(cs);
    *this += tmp;
    return *this;
}

String &String::operator+=(const char& c) {
    // add a single character to the string
    String tmp(1, c);
    *this += tmp;
    return *this;
}

size_t String::length() const {
    return sz;
}

size_t String::size() const {
    return sz;
}

size_t String::capacity() const {
    // return the capacity
    // ( the String can hold cap - 1 characters, the last character is always the terminator '\0' )
    return cap - 1;
}

// check if we have an empty string
bool String::empty() const {
    return *this == String();
}

// clear the string
void String::clear() {
    strcpy(p, "");
    // reset size
    sz = 0;
}

void String::push_back(const char& c) {
    // use the overloaded += for const char&
    *this += c;
}

// returns a reference to the character at index i
char& String::operator[](const size_t &i) {
    return p[i];
}

// returns a constant reference to the character at index i
const char& String::operator[] (const size_t& i) const {
    return p[i];
}

char& String::at(const size_t& pos) {
    if (pos < 0 || pos >= sz) {
        fprintf(stderr, "%s", "out_of_range exception!\n");
        // if we have an out of range error, return an empty character ( or something else? )
        return p[sz];
    } else {
        return p[pos];
    }
}

const char& String::at(const size_t& pos) const {
    if (pos < 0 || pos >= sz) {
        fprintf(stderr, "%s", "out_of_range exception!\n");
        // if we have an out of range error, return an empty character ( or something else? )
        return p[sz];
    }
    return p[pos];
}

String String::substr(const size_t& pos, const size_t& n) {
    // if pos is equal to the length of the string, return an empty string
    if (pos == this->length()) {
        return String();
    } else if (pos > this->length() || pos < 0) {
        // if pos is higher than the length of the string, return an empty string and an error
        fprintf(stderr, "%s", "out_of_range exception!\n");
        return String();
    } else {
        // if pos is smaller than the length of the String create a temporary string
        String tmp;
        // add characters to it
        for (size_t i = 0; (i < n) && (i + pos < sz); i++) {
            // check again if we don't go out of the range
            tmp += p[i + pos];
        }
        return tmp;
    }
}

const char* String::c_str() const {
    // return the internal buffer, which is a c-string
    return p;
}

const char* String::data() const {
    // return the internal buffer, which is a c-string
    return p;
}

void String::expandMem(const size_t& n) {
    // allocate memory for a temporary buffer
    char* tmp = (char*) malloc((cap) * sizeof(char));
    // copy the current buffer into the tmp buffer
    strcpy(tmp, p);
    // free the current buffer
    free(p);
    // allocate memory for the new buffer ( n extra bytes )
    p = (char*) malloc((cap + n) * sizeof(char));
    // copy back p's content
    strcpy(p, tmp);
    // free tmp
    free(tmp);
    // extend the capacity
    cap += n;
}
