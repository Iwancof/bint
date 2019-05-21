#include<bits/stdc++.h>
#include<stdio.h>
/*
#include<iostream>
#include<vector>
#include<cmath>
#include<algorithm>
#include<list>
#include<iterator>
*/

//#define not !
//#define and &&
//#define or ||

using namespace std;


class bint {
  public:
    //private:
    vector<bool> value; //先頭から下位ビット
    int digit; //ビット数

    //public:
    
    //Initialize
    bint(vector<bool> inp) {
      value.resize(inp.size());
      copy(inp.begin(),inp.end(),value.begin());
      digit = value.size();
      //cout << value.size() << endl;
    }

    int _convert_to_int_non_sign(bint x) { //x.valueを符号を無視して読み取る
      int res = 0;
      printf("size:%d,digit:%d\n",x.value.size(),x.digit);
      for(int i = 0;i < x.digit;i++) {
        cout << x.value[i] << endl;
        res += x.value[i] * pow(2,i);
      }
      return res;
    }

    int _convert_to_int_sign(bint x) {
      cout << x.value.size() << endl;
      if(x.value[x.digit - 1] == true) { //値がマイナスなら
        return _convert_to_int_non_sign(_reverse(x));
      } else if(x.value[x.digit - 1] == false) { //値がプラスなら
        return _convert_to_int_non_sign(x);
      }
    }

    bint _reverse(bint x) { //コピーしたbintを反転して+1して返す
      cout << x.value .size() << endl;
      vector<bool> v_x(x.value.size());
      copy(x.value.begin(),x.value.end(),v_x.begin());
      for(int i = 0;i < v_x.size();i++) 
        v_x[i] = !v_x[i];
      //v_x.push_back(false); //1000(-8)の時に処理後も1000になってしまうので(-)01000とすることで回避する
      //やっぱりいらない
      cout << v_x.size() << endl;
      return bint(v_x) + bint(vector<bool>{true,false});
    }

    int convert_to_int() {
      printf("in convert_int_int, size:%d,digit%d\nand ",
      return _convert_to_int_sign(*this);
    }

    int __convert_to_int() {
      if(value[value.size() - 1] == true) { //符号ビットで判定 true:マイナス
        return -_reverse(*this).__convert_to_int();
      }
      int res = 0;
      for(int i = 0;i < value.size() - 1;i++) {
        res += value[i] * pow(2,i);
      }

      return res;
    }




    //Operator overload

    //Half adder
    bool hfa(bool a,bool b) {
      return a ^ b;
    }

    //Full adder
    tuple<bool,bool> fla(bool a,bool b,bool c) {
      bool _v = (c and not(a ^ b)) or (b and not(a ^ c)) or (a and not(b ^ c));
      bool _c = (a and b) or (b and c) or (c and a);

      return make_tuple(_v,_c);
    }

    void value_pad(vector<bool> vec,int num,bool value) {
      while(vec.size() <= num)
        vec.push_back(false);
    }
    
    bint operator+(const bint& x) {
      vector<bool> v_res,v_this,v_x; //ローカル変数として、再定義
      
      v_this.resize(value.size());
      copy(value.begin(),value.end(),v_this.begin()); //v_thisにthis.valueをコピー
      v_x.resize(x.value.size());
      copy(x.value.begin(),x.value.end(),v_x.begin()); //v_xにx.valueをコピー

      //大きい桁の方に合わせる(符号ビットで埋める)
      int max_digit = std::max(v_this.size(),v_x.size());
      if(v_this.size() > v_x.size()) value_pad(v_x,max_digit,v_x[x.digit - 1]);
      else value_pad(v_this,max_digit,v_this[digit - 1]);

      //加算
      bool c = false; //繰り上がり
      tuple<bool,bool> receiver; //flaの返り値受け取り用タプル
      for(int i = 0;i < max_digit;i++) {
        receiver = fla(v_this[i],v_x[i],c);
        v_res.push_back(std::get<0>(receiver));
        c = std::get<1>(receiver);
      }
      
      //if(c == true) v_res.push_back(c); //最後の繰り上がり回収(falseで受け取らないのはむやみに桁が増えるのを防止するため)
      //v_res.push_back(c); //引き算の時に変になるので、falseの時も入れる。
      //v_res.push_back(false); //やっぱり変なのでfalse
      v_res.push_back(c); //でもこっちで行けそう？

      return bint(v_res);
    }
};

int main(void) {
  vector<bool> bv{false,true,false,true}; //5;
  bint v(bv);

  printf("size:%d,digit:%d\n",v.value.size(),v.digit);

  cout << v.convert_to_int() << endl;

  /*
  vector<bool> bv1{false,false,true,true}; //3;
  vector<bool> bv2{true,true,false,true}; //-3;

  reverse(bv1.begin(),bv1.end());
  reverse(bv2.begin(),bv2.end());

  bint v1(bv1);
  bint v2(bv2);

  cout << v1.value.size() << endl;
  
  

  printf("%d,%d,%d",v1.convert_to_int(),v2.convert_to_int(),(v1 + v2).convert_to_int());

  */
  
  
  
  return 0;
}
