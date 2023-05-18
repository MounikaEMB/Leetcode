// 121--->121-->True
// -121-->121- --> False

#include <stdio.h>
#include <stdbool.h>

bool isPalindrome(int x){
    int r=0,temp;
    int sum = 0;
    if(x<0) return false;
    temp = x;
    while(x>0)
    {
        r = x%10;
        sum = r+(sum*10);
        x = x/10;
    }
    return sum == x;
}

int main()
{
    int n;
    printf("Enter a number: ");
    scanf("%d", &n);
    bool result = isPalindrome(n);

    if (result) {
        printf("The number is a palindrome.\n");
    } else {
        printf("The number is not a palindrome.\n");
    }

    return 0;
}
