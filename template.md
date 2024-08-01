# 函数默认参数
# 模板函数
建立一个通用函数, 返回值类型和形参不具体指定, 使用泛化(虚拟的)的类型来表示.
```c++
template<typename T>
函数声明
```

### 场景
实现交换函数
```c++
void swap(int& a, int& b) {
    int temp = a;
    a = b;
    b = temp;
}
// 见名知意的要求, 函数名可能要改为
// swapInt
// 如果要交换double类型, 还需要一个swapDouble
void swapDouble(double& d1, double& d2){
    double temp = d1;
    d1 = d2;
    d2 = temp;
}

// 有了泛型编程之后
template<typename T>
void swap(T& t1, T& t2) {
    T temp = t1;
    t1 = t2;
    t2 = temp;
}
```
### 注意事项
- 自动类型推导, 必须推导出一致的数据类型T 才可以使用
- 模板必须要确定出T的数据类型才可以使用
```c++
int main(){
    double d1 = 2.2d;
    char c = 'a';
    // 推导类型不一致
    swap(d1, c);
    return 0; 
} 
```
```c++
template<typename T>
void func() {
    cout << "" << endl;
}
void test() {
    // 无法推导泛型类型 
    func();
}
```
## 模板的局限
```c++
// 对比两个数据是否相等
template<typename T>
bool myCompare(T &a, T& b){
    return a == b;
}
// 当使用自定义数据类型调用该函数时, 函数如何确定比较?
```
```c++
class Person{
public:
    std::string name;
    int age;
    Person(std::string name, int age): name(name), age(age){}
    void setName(std::string name) {
        this->name = name;
    }
    std::string getName() {
        return this->name;
    }
    void setAge(int age) {
        this->age = age;
    }
    int getAge() {
        return this->age;
    }
};
template<> bool myCompare(Person &a, Person& b){
    return a.getName() == b.getName() && a.getAge() == b.getAge();
}
```
# 模板类
建立一个通用类, 类中成员数据类型可以不具体制定, 使用泛化类型表示
```c++
template<class T>
类声明
```

```c++
template<class NameType, class AgeType>
class Person {
public:
 NameType name;
 AgeType age;
};
```

# 类和函数模板的区别
1. 类模板没有自动类型推导的使用方式
2. 类模板在模板参数列表中可以有默认参数

```c++
template<class NameType, class AgeType>
class Person {
public:
 NameType name;
 AgeType age;
 // all constructor & getter & setter 
};

// 类模板没有自动类型推导的使用方式
void test1() {
    // 类模板无法直接从构造推导
    Person p("Sika", 11);
    Person<string, int> p("Sika", 11);
}
```

```c++
// 默认第二个参数类型为int, 在不指定的情况下即为int
template<class NameType, class AgeType = int>
class Person {
public:
 NameType name;
 AgeType age;
 // all constructor & getter & setter 
};

void test2() {
    // 类模板在模板参数列表中可以有默认参数
    Person<string> p("Sika", 11);
}
```
