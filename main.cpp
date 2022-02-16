#include <iostream>

std::string delete_leading_zeroes(std::string num)
{
    std::string result;
    for (int i = 0; i < num.length(); i++) {
        if (num[i] == '0') {
            continue;
        }  else {
            result += num[i];
        }
    }
    return result;
}

bool checking_numbers(std::string longNum, bool firstAttempt)
{
    int pointControl = 0;
    int digitControl = 0;
    bool correct = true;

    if (firstAttempt) {
        return false;
    }

    for (int i = 0; i < longNum.length(); i++) {

        if ((longNum[i]>='0') && (longNum[i]<='9')) {
            digitControl++;
        }

        if (longNum[i]=='.') {
            pointControl++;
        }

        if ((i == 0) && ((longNum[i]!='.') && (longNum[i]!='-') &&
                         !((longNum[i]>='0') && (longNum[i]<='9')))) {
            correct = false;
            std::cout << "Error: the first character must be digit, minus sign or dot." << std::endl;
            std::cout << "Repeat the input!" << std::endl;
        }

        if ((i > 0) && ((longNum[i]!='.') &&
                        !((longNum[i]>='0') && (longNum[i]<='9')))) {
            std::cout << "Error: a number record contains garbage characters!" << std::endl;
            std::cout << "Repeat the input!" << std::endl;
            correct = false;
        }
    }

    if (digitControl==0 || pointControl>1) {
        std::cout << "Error: Incorrect amount of dots or digits!" << std::endl;
        std::cout << "Repeat the input!" << std::endl;
        correct = false;
    }

    return correct;
}

int dot_position(std::string longNum)
{
    int dotPosition = -1;
    for (int i = 0; i < longNum.length(); i++) {
        if (longNum[i] == '.') {
            dotPosition = i;
            break;
        }
    }
    if (dotPosition == -1) dotPosition = longNum.length();

    return dotPosition;
}

int max_frac_length(std::string longNum1, std::string longNum2)
// The function obtains the maximal length of a number's
// fractional part between two numbers
{
    int dotPos1 = dot_position(longNum1);
    int dotPos2 = dot_position(longNum2);

    int maxFracLength = longNum1.length() - dotPos1;
    if (longNum1.length() - dotPos1<0) maxFracLength = 0;
    int fracLength2 = longNum2.length() - dotPos2;
    if (fracLength2>maxFracLength) maxFracLength = fracLength2;

    return maxFracLength;
}

int comparePositiveNums(std::string longNum1, std::string longNum2)
{
    int result = 0;
    int dotPos1 = dot_position(longNum1);
    int dotPos2 = dot_position(longNum2);

    // Integer part
    if (dotPos1>dotPos2) {
        result = 1;
    } else if (dotPos1<dotPos2) {
        result = -1;
    } else if (dotPos1>0) {
        for (int i = 0; i < dotPos1; i++) {
            if (longNum1[i]>longNum2[i]) {
                result = 1;
                break;
            } else if (longNum1[i]<longNum2[i]) {
                result = -1;
                break;
            }
        }
    }

    // Fractional part
    int fracChar1 = '0';
    int fracChar2 = '0';

    int maxFracLength = max_frac_length(longNum1, longNum2);
    for (int i = 0; i < maxFracLength; i++) {

        if (dotPos1 + i + 1 > longNum1.length() - 1) {
            fracChar1 = '0';
        } else {
            fracChar1 = longNum1[dotPos1 + i + 1];
        }

        if (dotPos2 + i + 1 > longNum2.length()-1) {
            fracChar2 = '0';
        } else {
            fracChar2 = longNum2[dotPos2 + i + 1];
        }

        if (fracChar1>fracChar2) {
            result = 1;
            break;
        } else if (fracChar1<fracChar2) {
            result = -1;
            break;
        }
    }

    return result;
}

int compareNums(std::string longNum1, std::string longNum2)
{
    std::string absNum1;
    std::string absNum2;
    int absResult = 0;
    int result = 0;

    int neg1 = 0;
    int neg2 = 0;

    if (longNum1[0] == '-') neg1 = 1;
    if (longNum2[0] == '-') neg2 = 1;

    for (int i = neg1; i < longNum1.length(); i++) {
        absNum1 += longNum1[i];
    }

    for (int i = neg2; i < longNum2.length(); i++) {
        absNum2 += longNum2[i];
    }

    //std::cout << "Absolute value of N1 and N2: " << absNum1 << ",  " << absNum2 << std::endl;
    absResult =  comparePositiveNums(absNum1, absNum2);

    if ((neg1 == 0) && (neg2 == 1)) {
        result = 1;
    } else if ((neg1 == 1) && (neg2 == 0)) {
        result = -1;
    } else if (((neg1 == 0) && (neg2 == 0)) && (absResult > 0)) {
        result = 1;
    } else if (((neg1 == 0) && (neg2 == 0)) && (absResult < 0)) {
        result = -1;
    } else if (((neg1 == 1) && (neg2 == 1)) && (absResult > 0)) {
        result = -1;
    } else if (((neg1 == 1) && (neg2 == 1)) && (absResult < 0)) {
        result = 1;
    }  else {
        result = 0;
    }

    return result;
}

std::string correctedNums(std::string num)
{
    std::string corNum;
    std::string corNum1;
    corNum1 = num;
    int neg = 0;
    bool isNotNull = false;

    for (int i = 0;i < num.length(); i++) {
        if (!((num[i] != 0) && (num[i] != '.' ) && (num[i] != '-' ))) {
            isNotNull = true;
            break;
        }
    }

    // If there are no characters different from '-', '.' or '0',
    // it is zero (without minus, if it was)!
    if (isNotNull == false) {
        corNum = "0.0";
        return corNum;
    }

    int startInd = 0;
    if (num[0] == '-') {
        neg = 1;
        startInd = 1;
        for (int i = startInd; i < num.length(); i++) {
            corNum1 += num[i];
        }
    }

    char firstChar = '0';
    int dotPos1 = dot_position(corNum1);
    int corNum1Lenth = corNum1.length();

    if (dotPos1 == 0) {
        corNum = '0';
        corNum += corNum1;
    } else {
        // Delete leading zeroes if any
        bool noLeadingZeroes = true;
        for (int i = 0; ((i < dotPos1) && (noLeadingZeroes)); i++) {
            if ((corNum1[i] == '0') && (corNum1[i+1] != '.')) {
                continue;
            }
            corNum += corNum1[i];
        }

        // Fractional part
        int fracLength = corNum1Lenth - dotPos1;
        std::string fracPartInv;

        for (int i = 1; i < fracLength; i++) {
            fracPartInv += corNum1[corNum1Lenth - i];
        }
        std::string fracPartInvNew = delete_leading_zeroes(fracPartInv);

        corNum += '.';
        for ( int i = 0; i < fracPartInvNew.length(); i++) {
            corNum += fracPartInvNew[fracPartInvNew.length() - i];
        }
    }
    return corNum;
}

int main() {

    std::cout << "                         \n";
    std::cout << "Long real number's comparison \n";
    std::cout << "                         \n";

    int result;
    std::string longNumber1;
    std::string longNumber2;
    std::string longNum;



    for (int i = 0; i < 2; i++) {
        bool firstAttempt = true;
        while (!(checking_numbers(longNum, firstAttempt))) {
            std::cout << "Input number " << (i+1) << ": ";
            std::cin >> longNum;
            firstAttempt = false;
        }
        if (i == 0) {
            longNumber1 = longNum;
            longNum = "";
        } else if (i == 1) {
            longNumber2 = longNum;
            longNum = "";
        }
    }

    std::string corrLongNumber1 = correctedNums(longNumber1);
    std::string corrLongNumber2 = correctedNums(longNumber2);

    result = compareNums(longNumber1, longNumber2);

    if (result>0) {
        std::cout << "N1 is more than N2!";
    } else if (result<0) {
        std::cout << "N1 is less than N2!";
    } else {
        std::cout << "N1 is equal to N2!";
    }
}
