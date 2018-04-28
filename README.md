# split_train_val
## Purpose
To randomly split datasets into train datasets and validation datasets with the specific ratio(like 0.2)<br> 
## Requirement
* 1、Visual Studio<br>
* 2、{your categories}.txt, the content like this<br>
0,bus<br>
1,bazaar<br>
2,church<br>
3,cafe<br>
……<br>
{id},{category}<br>
* 3、{category_mapping}.txt, the content like this<br>
2b2b344f-1c85-11e8-aaf5-00163e025669,0<br>
1dcd5677-1c83-11e8-aaf2-00163e025669,0<br>
864f56ad-1c85-11e8-aaf5-00163e025669,0<br>
54b25ede-1c83-11e8-aaf2-00163e025669,0<br>
1450b4f8-1c83-11e8-aaf2-00163e025669,0<br>
{file_name},{category}<br>
## Introduction
The first two parameters are {your categories}.txt {category_mapping}.txt file. These txt file are in the path where you store {your cpp file}.<br> 
The third parameter is the number of category. <br>
The last parameter controls the validation datasets ratio.<br>
```cpp
SplitData::SplitData(std::string categories, std::string list, int _categories_num, float ratio)
```
Please ensure that the two txt file are well-formatted.
<br>
The member function moving. It require one parameter which is the path to the original datasets.<br>
```cpp
void SplitData::moving(std::string source_dir)
```
## Usage
Call the constructor function with the required 4 parameters.<br>
Then call the member function to split datasets into two folder. Each folder(train/validation) contains the folders which store the 
data belonging to each category.
The directory structure should like this.
![result directory structure](https://github.com/Zerahhah/split_train_val/blob/master/result.png)
