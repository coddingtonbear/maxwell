#include <HashMap.h>

//define HashMap
HashMap<String, int> hashMap;

void setup(){
  //setup hashmap
  hashMap.put("name",18);
  hashMap.put("test",200);
  hashMap.put("qwer",1234);
  hashMap.put("abc",123);
  hashMap.put("AlphaBeta",20);
  
  Serial.begin(9600);

  Serial.println(hashMap.valueFor("test"), DEC );
  
}

void loop(){/*nothing to loop*/}