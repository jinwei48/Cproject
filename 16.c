#include <stdio.h>
#include <time.h>

// 定义HealthProfile结构体
typedef struct {
    char firstname[50];
    char LastName[50];
    char gender[10];
    int dob_year;
    int dob_month;
    int dob_day;
    float height_in; // 身高，单位为英寸
    float weight_lb; // 体重，单位为磅
    int age;         // 年龄
    float max_heart_rate; // 最高心跳速率
    float target_heart_rate_min; // 目标心跳速率范围最小值
    float target_heart_rate_max; // 目标心跳速率范围最大值
} HealthProfile;

// 计算BMI的函数
float calculateBMI(HealthProfile profile) {
    // 计算BMI
    return (profile.weight_lb / ((profile.height_in / 39.37) * (profile.height_in / 39.37)));
}

// 计算年龄的函数
void calculateAge(HealthProfile *profile) {
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    int current_year = tm.tm_year + 1900;
    int current_month = tm.tm_mon + 1;
    int current_day = tm.tm_mday;

    profile->age = current_year - profile->dob_year;
    if (current_month < profile->dob_month || (current_month == profile->dob_month && current_day < profile->dob_day)) {
        profile->age--;
    }
}

// 计算最高心跳速率的函数
float calculateMaxHeartRate(HealthProfile profile) {
    return 220 - profile.age;
}

// 计算目标心跳速率范围的函数
void calculateTargetHeartRate(HealthProfile *profile) {
    profile->max_heart_rate = calculateMaxHeartRate(*profile);
    profile->target_heart_rate_min = profile->max_heart_rate * 0.5;
    profile->target_heart_rate_max = profile->max_heart_rate * 0.85;
}

int main() {
    HealthProfile profile; // 定义HealthProfile类型的变量

    // 输入个人信息
    printf("your firstname:");
    scanf("%s", profile.firstname);
    printf("your LastName:");
    scanf("%s", profile.LastName);
    printf("your gender:");
    scanf("%s", profile.gender);
    printf("your date of birth (year month day):");
    scanf("%d %d %d", &profile.dob_year, &profile.dob_month, &profile.dob_day);
    printf("your height (inches):");
    scanf("%f", &profile.height_in);
    printf("your weight (pounds):");
    scanf("%f", &profile.weight_lb);

    // 计算年龄、最高心跳速率和目标心跳速率范围
    calculateAge(&profile);
    calculateTargetHeartRate(&profile);

    // 计算BMI
    float bmi = calculateBMI(profile);

    // 显示结果
    printf("\nyour BMI:%.2f\n", bmi);
    printf("youe age:%d\n", profile.age);
    printf("max_rate:%.2f per/min\n", profile.max_heart_rate);
    printf("range:%.2f - %.2fper/min\n", profile.target_heart_rate_min, profile.target_heart_rate_max);

    return 0;
}