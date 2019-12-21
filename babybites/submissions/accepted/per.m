#import <stdio.h>
#import <Foundation/Foundation.h>

int main() {
  int n;
  char str[1000];
  scanf("%d", &n);
  for (int i = 1; i <= n; ++i) {
      scanf("%s", str);
      if (strcmp(str, "mumble") && atoi(str) != i) {
          printf("something is fishy");
          return 0;
      }
  }
  printf("makes sense");
  return 0;
}
