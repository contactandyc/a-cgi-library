# Overview of A CGI Library

ACGI is a key/value CGI parser library written in C, designed to simplify the parsing and handling of CGI data in URLs.  There are functions for decoding CGI strings, extracting key-value pairs, and converting them to various data types. 

## Dependencies

* [A memory library](https://github.com/contactandyc/a-memory-library) for efficient memory handling.
* [A JSON library](https://github.com/contactandyc/a-json-library) for converting CGI data to JSON format.

## Installation

### Clone the library and change to the directory

```bash
git clone https://github.com/contactandyc/a-cgi-library.git
cd a-cgi-library
```

### Build and install the library

```bash
mkdir -p build
cd build
cmake ..
make
make install
```

## An Example

```c
#include <stdio.h>
#include "a-cgi-library/acgi.h"
#include "a-memory-library/aml_pool.h"

int main() {
    // Sample CGI query string
    const char* cgi_str = "name=John+Doe&age=30&is_student=false";

    // Create a memory pool for memory management (required for acgi)
    aml_pool_t *pool = aml_pool_init(1024);

    // Initialize a CGI object
    acgi_t *cgi = acgi_init(pool, cgi_str);

    // Extract data from the CGI query
    const char* name = acgi_str(cgi, "name", "unknown");
    int age = acgi_int(cgi, "age", -1);
    bool is_student = acgi_bool(cgi, "is_student", false);

    // Print the values
    printf("Name: %s\n", name);
    printf("Age: %d\n", age);
    printf("Is Student: %s\n", is_student ? "true" : "false");

    // Clean up
    aml_pool_destroy(pool);
    return 0;
}
```

## Core Functions

- **acgi_init**: Initializes a CGI object using a memory pool.
- **acgi_to_json**: Converts CGI data to a JSON object.
- **acgi_query**: Retrieves the original CGI query.

## Data Type Conversion

- **acgi_strs**: Returns a NULL-terminated array of decoded values for a given key.
- **acgi_str**: Retrieves the first decoded string for a given key.
- **acgi_bool**: Converts the first decoded string of a key to a boolean.
- **acgi_int**: Converts the first decoded string of a key to an integer.
- **acgi_long**: Converts the first decoded string of a key to a long.
- **acgi_double**: Converts the first decoded string of a key to a double.
- **acgi_int32**: Retrieves a 32-bit integer from the CGI data.
- **acgi_uint32**: Retrieves an unsigned 32-bit integer from the CGI data.
- **acgi_int64**: Retrieves a 64-bit integer from the CGI data.
- **acgi_uint64**: Retrieves an unsigned 64-bit integer from the CGI data.

## Decoding Function

- **acgi_decode**: Decodes CGI text.
