#include <iostream>
#include <vector>

using namespace std;

class SET{
 public:
  vector<int> v;
  int size;
  SET():size(0){}
  int Insert(int data){
    if(size == 0){
      v.push_back(data);
      size++;
      return size;
    }
    else if(v[0]>data){
      v.insert(v.begin(),data);
      size++;
      return size;
    }
    else{
      int begin = 0;
      int end = size;
      int mid;
      for(;begin<end-1;){
        mid = (begin + end)/2;
        if(v[mid] == data){
          return size;
        }
        else if(v[mid] > data){
          end = mid;
        }
        else{
          begin = mid;
        }
      }
    if(v[begin] == data){
          return size;
        }
    v.insert(v.begin()+begin+1,data);
    size++;
    return size;
    }
  }

  int Delete(int data){
    int begin = 0;
    int end = size;
    int mid;
    for(;begin<end-1;){
      mid = (begin+end)/2;
      if(v[mid] == data){
        v.erase(v.begin()+mid,v.begin()+mid+1);
        return --size;
      }
      else if(v[mid] > data){
          end = mid;
        }
      else{
          begin = mid;
        } 
    }
    return size;
  }

  void Print(){
    if(size==0){
      cout<<endl;
    }
    else{
    for(int i = 0; i < size; i++){
      if(i < size - 1){
      cout<<v[i]<<",";
      }
      else{
	cout<<v[i]<<endl;
      }
    }}
  }

  int Belongs_To(int data){
    if(size == 0){
      return 0;
    }
    if(v[0]==data){
      return 1;
    }
    int begin = 0;
    int end = size-1;
    for(;begin<=end;){
      int mid = begin + (end - begin)/2;
      if(v[mid] == data){
        return 1;
      }
      else if(v[mid] > data){
          end = mid-1;
        }
      else{
          begin = mid+1;
        } 
    }
    return 0;
  }
  int Size(){
    return size;
  }

  int Union(SET other){
    vector<int> v1;
    int i = 0;
    int j = 0;
    while (i < v.size() && j < other.v.size()){
      if(v[i]<other.v[j]){
        v1.push_back(v[i]);
        i++;
      }
      else if(v[i]>other.v[j]){
        v1.push_back(other.v[j]);
        j++;
      }
      else{
        v1.push_back(v[i]);
        i++;
        j++;
      }
    }
    if (i < v.size()){
        for(;i < v.size();){
            v1.push_back(v[i]);
            i++;
        }
    }
    if (j < other.v.size()){
        for(;j < other.v.size();){
            v1.push_back(other.v[j]);
            j++;
        }
    }
    v = v1;
    size = v.size();
    return size;
  }

  int Intersection(SET other){
    vector<int> v2;
    int i = 0;
    int j = 0;
    while (i < v.size() && j < other.v.size()){
      if(v[i] == other.v[j]){
        v2.push_back(v[i]);
        i++;
        j++;
      }
      else if(v[i]< other.v[j]){
        i++;
      }
      else{
        j++;
      }
    }
    v = v2;
    size = v.size();
    return size;
  }

  int Difference(SET other){
    vector<int> v1;
    int i = 0;
    int j = 0;
    while (i < v.size() && j < other.v.size()){
      if(v[i]<other.v[j]){
        v1.push_back(v[i]);
        i++;
      }
      else if(v[i]>other.v[j]){
        j++;
      }
      else{
        i++;
        j++;
      }
    }
    if (i < v.size()){
        for(;i < v.size();){
            v1.push_back(v[i]);
            i++;
        }
    }
    v = v1;
    size = v.size();
    return size;
  }

  int Sym_Difference(SET other){
    vector<int> v1;
    int i = 0;
    int j = 0;
    while (i < v.size() && j < other.v.size()){
      if(v[i]<other.v[j]){
        v1.push_back(v[i]);
        i++;
      }
      else if(v[i]>other.v[j]){
        v1.push_back(other.v[j]);
        j++;
      }
      else{
        i++;
        j++;
      }
    }
    if (i < v.size()){
        for(;i < v.size();){
            v1.push_back(v[i]);
            i++;
        }
    }
    else if (j < other.v.size()){
        for(;j < other.v.size();){
            v1.push_back(other.v[j]);
            j++;
        }
    }
    v = v1;
    size = v.size();
    return size;
  }
};


int main(void){
  int func;
  vector<SET> sets;
  int setnum;
  int data;
  int setnum1;
  int setnum2;
  for(;cin>>func;){
    switch(func){
        case 1:
        cin >> setnum>>data;
        if (setnum < sets.size()){
            cout<<sets[setnum].Insert(data)<<endl;
        }
        else{
            SET set = SET();
            cout<<set.Insert(data)<<endl;
            sets.push_back(set);
        }
        break;

        case 2:
        cin >> setnum>>data;
        if (setnum < sets.size()){
            cout<<sets[setnum].Delete(data)<<endl;
        }
        else{
            cout << -1<<endl;
        }
        break;

        case 3:
        cin >> setnum>>data;
        if (setnum < sets.size()){
            cout<<sets[setnum].Belongs_To(data)<<endl;
        }
        else{
            cout << -1<<endl;
        }
        break;

        case 4:
        cin >> setnum1>>setnum2;
        if (setnum1 < sets.size() && setnum2 < sets.size()){
            cout<<sets[setnum1].Union(sets[setnum2])<<endl;
        }
        else {
          if (setnum1 != setnum2 && setnum1 >= sets.size() && setnum2 >= sets.size()){
            SET set1 = SET();
            SET set2 = SET();
            sets.push_back(set1);
            sets.push_back(set2);
            cout<<0<<endl;
          }
          else{
            SET set = SET();
            sets.push_back(set);
            cout<<sets[setnum1].Union(sets[setnum2])<<endl;
          }
        }
        break;

        case 5:
        cin >> setnum1>>setnum2;
        if (setnum1 < sets.size() && setnum2 < sets.size()){
            cout<<sets[setnum1].Intersection(sets[setnum2])<<endl;
        }
        else {
            if (setnum1 != setnum2 && setnum1 >= sets.size() && setnum2 >= sets.size()){
            SET set1 = SET();
            SET set2 = SET();
            sets.push_back(set1);
            sets.push_back(set2);
            cout<<0<<endl;
          }
          else{
            SET set = SET();
            sets.push_back(set);
            cout<<sets[setnum1].Intersection(sets[setnum2])<<endl;
          }
        }
        break;

        case 6:
        cin >> setnum;
        if (setnum < sets.size()){
            cout<<sets[setnum].Size()<<endl;
        }
        else {
            SET set = SET();
            cout<<0<<endl;
            sets.push_back(set);
        }
        break;

        case 7:
        cin >> setnum1>>setnum2;
        if (setnum1 < sets.size() && setnum2 < sets.size()){
            cout<<sets[setnum1].Difference(sets[setnum2])<<endl;
        }
        else {
            if (setnum1 != setnum2 && setnum1 >= sets.size() && setnum2 >= sets.size()){
            SET set1 = SET();
            SET set2 = SET();
            sets.push_back(set1);
            sets.push_back(set2);
            cout<<0<<endl;
          }
          else{
            SET set = SET();
            sets.push_back(set);
            cout<<sets[setnum1].Difference(sets[setnum2])<<endl;
          }
        }
        break;

        case 8:
        cin >> setnum1>>setnum2;
        if (setnum1 < sets.size() && setnum2 < sets.size()){
            cout<<sets[setnum1].Sym_Difference(sets[setnum2])<<endl;
        }
        else {
            if (setnum1 != setnum2 && setnum1 >= sets.size() && setnum2 >= sets.size()){
            SET set1 = SET();
            SET set2 = SET();
            sets.push_back(set1);
            sets.push_back(set2);
            cout<<0<<endl;
          }
          else{
            SET set = SET();
            sets.push_back(set);
            cout<<sets[setnum1].Sym_Difference(sets[setnum2])<<endl;
          }
        }
        break;

        case 9:
        cin >> setnum;
        if (setnum < sets.size()){
            sets[setnum].Print();
        }
        else {
            cout<<endl;
        }
        break;

        default:
        return -1;
    }
  }
  return 0;
}
