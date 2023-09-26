//maze
byte path[100];      //shortest path in the maze
byte revpath[100];   //reversed shortest path
byte tos_addr = -1;  //variable to indicate address of the top value of path array

//-------------------------------------------------------------------------------------------------------

void maze() {
  while (1) {
    read_IR();  //read IR sensor array which consist 6 IRs [0,1,2,3,4,5]
    //------------------------------------
    for (int i = 0; i < 7; i++) {
      Serial.print(IR_val[i]);
      Serial.print(" , ");
    }
    Serial.println();
    //-------------------------------------------
    if ((IR_val[0] == 1 and IR_val[1] == 1) and (IR_val[4] == 0 and IR_val[5] == 0)) {
      Serial.println("We are at a Junction");
      force_forward();
      //pid_forward(F);
      read_IR();
      //------------------------------------
      for (int i = 0; i < 7; i++) {
        Serial.print(IR_val[i]);
        Serial.print(" , ");
      }
      Serial.println();
      //-------------------------------------------
      if (IR_val[1] == 0 and IR_val[2] == 0 and IR_val[3] == 0 and IR_val[4] == 0) {
        Serial.println("We are at a L Junction");
        Serial.println("Turning Left");
        turn_leftn();
      } else {
        tos_addr = tos_addr + 1;
        path[tos_addr] = 1;
        Serial.println("We are at Straight or left Junction");
        Serial.println("Turning Left");
        turn_leftn();
        continue;
      }
    } else if ((IR_val[0] == 0 and IR_val[1] == 0) and (IR_val[4] == 1 and IR_val[5] == 1)) {
      Serial.println("We are at a junction");
      force_forward();
      read_IR();
      //------------------------------------
      for (int i = 0; i < 7; i++) {
        Serial.print(IR_val[i]);
        Serial.print(" , ");
      }
      Serial.println();
      //-------------------------------------------
      if (IR_val[1] == 0 and IR_val[2] == 0 and IR_val[3] == 0 and IR_val[4] == 0) {
        Serial.println("We are at a L Junction");
        Serial.println("Turning Right");
        turn_rightn();
      } else {
        tos_addr = tos_addr + 1;
        path[tos_addr] = 2;
        Serial.println("We are at a Straight or right Junction");
        Serial.println("Moving Straight");
        force_forward();
        continue;
      }
    } else if ((IR_val[0] == 1 and IR_val[1] == 1) and (IR_val[4] == 1 and IR_val[5] == 1)) {
      Serial.println("We are at a junction ");
      force_forward();
      read_IR();
      if (IR_val[1] == 1 and IR_val[4] == 1) {
        Serial.println("We are at the end");
        break;
      } else {
        Serial.println("We are at T junction or We are ar 4 way junction");
        Serial.println("Turning left");
        tos_addr = tos_addr + 1;
        path[tos_addr] = 1;
        turn_leftn();
        continue;
      }
    } else if (IR_val[0] == 0 and IR_val[1] == 0 and IR_val[2] == 0 and IR_val[3] == 0 and IR_val[4] == 0 and IR_val[5] == 0) {
      Serial.println("We are at the deadend");
      turn_leftn();  //turn_180
      tos_addr = tos_addr + 1;
      path[tos_addr] = 0;
      force_forward();
    } else {
      Serial.println("Moving Forward");
      pid_forward(15);
    }
  }
}

//---shortest_path-----------------------------------------------------------------------------------------
void shortpath(){
    int i=0;
    int temp;
    while(i<=tos_addr){
        if(path[i]==0){
            temp=(path[i-1]+path[i+1])%4;
            path[i-1]=temp;
            while(i+2<=tos_addr){
                path[i]=path[i+2];
                i++;
            }
            tos_addr=tos_addr-2;
            i=0;
        }
        else{
            i++;
        }
    }
}

void gomaze(int num) {
    if (num==1){
        turn_leftn();
    }
    else if(num==2){
        force_forward();
    }
    else{
        turn_rightn();
    }

    
}

//-----------------------------------------------------------------------------------------------------------

void revmaze() {
    m=0;
  while (m<=tos_addr) {
    read_IR();  //read IR sensor array which consist 6 IRs [0,1,2,3,4,5]
    //------------------------------------
    for (int i = 0; i < 7; i++) {
      Serial.print(IR_val[i]);
      Serial.print(" , ");
    }
    Serial.println();
    //-------------------------------------------
    if ((IR_val[0] == 1 and IR_val[1] == 1) and (IR_val[4] == 0 and IR_val[5] == 0)) {
      Serial.println("We are at a Junction");
      force_forward();
      //pid_forward(F);
      read_IR();
      //------------------------------------
      for (int i = 0; i < 7; i++) {
        Serial.print(IR_val[i]);
        Serial.print(" , ");
      }
      Serial.println();
      //-------------------------------------------
      if (IR_val[1] == 0 and IR_val[2] == 0 and IR_val[3] == 0 and IR_val[4] == 0) {
        Serial.println("We are at a L Junction");
        Serial.println("Turning Left");
        turn_leftn();
      } else {
          Serial.println("Looking up in revpath stack");
          gomaze(revpath[m]);
          m++;
      }
    } else if ((IR_val[0] == 0 and IR_val[1] == 0) and (IR_val[4] == 1 and IR_val[5] == 1)) {
      Serial.println("We are at a junction");
      force_forward();
      read_IR();
      //------------------------------------
      for (int i = 0; i < 7; i++) {
        Serial.print(IR_val[i]);
        Serial.print(" , ");
      }
      Serial.println();
      //-------------------------------------------
      if (IR_val[1] == 0 and IR_val[2] == 0 and IR_val[3] == 0 and IR_val[4] == 0) {
        Serial.println("We are at a L Junction");
        Serial.println("Turning Right");
        turn_rightn();
      } else {
          Serial.println("Looking up in revpath stack");
          gomaze(revpath[m]);
          m++;
      }
    } else if ((IR_val[0] == 1 and IR_val[1] == 1) and (IR_val[4] == 1 and IR_val[5] == 1)) {
      Serial.println("We are at a junction ");
      force_forward();
      read_IR();
      if (IR_val[1] == 1 and IR_val[4] == 1) {
        Serial.println("We are at the end");
        break;
      } else {
          Serial.println("Looking up in revpath stack");
          gomaze(revpath[m]);
          m++;
      }
    } else if (IR_val[0] == 0 and IR_val[1] == 0 and IR_val[2] == 0 and IR_val[3] == 0 and IR_val[4] == 0 and IR_val[5] == 0) {
      Serial.println("We are at the deadend");
      turn_leftn();  //turn_180
      force_forward();
    } else {
      Serial.println("Moving Forward");
      pid_forward(15);
    }
  }
  Serial.print("End Of The Maze Stage");
}

//----------------------------------------------------------------------------------------------------------

void rev(){
    m=tos_addr;
    while(m>=0){
        if (path[m]==3){
            revpath[tos_addr-m]=1;
        }
        else if(path[m]==1){
            revpath[tos_addr-m]=3;
        }
        else{
            revpath[tos_addr-m]=path[m];
        }
        m=m-1;
    }
    m=0;
}

//-------------------------------------------------------------------------------------------------------------------

void end_maze(){
  while(IR_val[0]!=1 or IR_val[1]!=1 or IR_val[2]!=1 or IR_val[3]!=1 or IR_val[4]!=1 or IR_val[5]!=1){
    pid_forward(15);
    read_IR();
    }
    stop();
    delay(1000);
  }

