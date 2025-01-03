# Get Next Line

**Get Next Line** is a function that reads a line from a file descriptor. It allows you to retrieve a line of text from a file one at a time without loading the entire file into memory. This project provides an efficient way to handle files line-by-line, especially for large files or streaming data.

---

## Features

- **Line-by-line reading**: Efficiently retrieves one line at a time from a file.
- **Memory-efficient**: Only loads the necessary parts of the file into memory.
- **Handles partial lines**: Correctly handles situations where a line is split across multiple reads.
- **Works with large files**: Efficient memory management allows it to work with files of any size.

---

## How It Works

The function reads the content of a file descriptor one chunk at a time and stores it in a static buffer. When a newline (`\n`) is encountered, it returns the current line and removes it from the buffer, leaving any remaining data to be processed in future calls. This allows subsequent calls to resume where the last read left off, without needing to reload the entire file.

### Key Functions:

- `get_next_line(int fd)`: The main function that reads and returns the next line.
- `extract_line()`: Extracts a single line from the buffer.
- `update_cache()`: Updates the buffer to remove the line that was just read.
- `fun_help()`: Handles reading from the file and appending to the buffer.

---

## Requirements

- C compiler (e.g., GCC)
- `BUFFER_SIZE` defined as a preprocessor macro, which specifies the chunk size for reading from the file.

---

## Usage

To use the `get_next_line` function:

1. Call the function with a valid file descriptor.
2. The function returns one line at a time from the file.
3. Once the end of the file is reached, it returns `NULL`.

```c
#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>

int main() {
    int fd = open("file.txt", O_RDONLY);
    char *line;

    while ((line = get_next_line(fd)) != NULL) {
        printf("%s", line);
        free(line);
    }

    close(fd);
    return 0;
}
```

---

## Compilation

To compile the project, run:

```bash
gcc -Wall -Wextra -Werror -D BUFFER_SIZE=32 get_next_line.c -o get_next_line
```

---

## Notes

- **Static Buffer**: The function uses a static buffer to store the leftover data between function calls.
- **Memory Management**: Be sure to free the returned lines after use to prevent memory leaks.
- **Error Handling**: The function returns `NULL` in case of an error or when the end of the file is reached.
