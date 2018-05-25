# split_train_val
## Purpose
To use Pytorch ImageFolder automatically loading train and validation dataset,the code randomly split the raw datasets(cannot use ImageFolder) into train datasets and validation datasets with the specific ratio(like 0.2). And the split datasets are stored in their subfolders separately.<br> 
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
{file_name},{id}<br>
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
The member function save_to_txt with no parameter creates train.txt and val.txt in your cpp_file's path.<br>
The member function save_to_txt with one parameter creates train.txt and val.txt in the path you want.<br>
```cpp
void SplitData::save_to_txt()
```
```cpp
void SplitData::save_to_txt(std::string target_dir)
```
## Usage
1)Call the constructor function with the required 4 parameters.<br>
2-1)Then call the member function to split datasets into two folder. Each folder(train/validation) contains the folders which store the 
data belonging to each category.
The directory structure should like this.
![result directory structure](https://github.com/Zerahhah/split_train_val/blob/master/result.png)
2-2)If you do not want to create the subfolders or copy file into the subfolders(creating subfolders and cpoying files means double disk space, but it is friendly to Pytorch.torchvision.ImageFolder), you can call the member function save_to_txt. Then the train filenames and val filenames are separately saved to the train.txt and val.txt in your cpp_file's path or the path you want.
