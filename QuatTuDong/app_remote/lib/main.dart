import 'package:flutter/material.dart';

void main() {
  runApp(const MyApp());
}

class MyApp extends StatelessWidget {
  const MyApp({super.key});

  @override
  Widget build(BuildContext context) {
    return MaterialApp(
      debugShowCheckedModeBanner: false,
      home: Scaffold(
        appBar: AppBar( centerTitle: true,
          backgroundColor: Colors.green,
          title:  Text( 'App Remote'),
          titleTextStyle: TextStyle( fontSize: 25, color: Colors.white),
          ),

        body: 
          ListView(

            padding: EdgeInsets.all( 10),

            children: <Widget>[
              Container(
                height:  320,
                decoration: BoxDecoration(
                  color: Colors.grey,
                  borderRadius: BorderRadius.circular(0)
                ),

                child: Column(
                  children: [
                    Expanded(child: Container(
                      color: Colors.amber,
                    )),

                    // OutlinedButton.icon(
                    //     style: OutlinedButton.styleFrom(
                    //       side: BorderSide( color: Colors.black),
                    //     ),
                    //     icon: Icon( Icons.reset_tv, size: 20,),
                    //     label: Text( 'Button',
                    //                   style: TextStyle( fontSize: 30),
                    //     ),
                    //     onPressed: (){},
                    //   ),

                    Expanded(child: Container(
                      color: Colors.red,
                      child: Row(
                        children: [
                          Padding(
                            padding: const EdgeInsets.only( left:  170),
                            child: ElevatedButton(onPressed: () {
                              // ĐÂY LÀ NƠI XỬ LÍ SỰ KIỆN KHI BUTTON ĐƯỢC THAO TÁC
                            },
                            style: ButtonStyle(
                              minimumSize: MaterialStateProperty.all( Size( 100, 50)),
                            ),
                            child: Text( 'Temp'),
                            ),
                          )
                        ],
                      )
                    )),

                    Expanded(
                      child: Container(
                        color: Colors.yellow, // Bỏ thuộc tính này hoặc thay đổi màu nền tại đây
                        child: Row(
                          children: [
                            Container(
                              padding: EdgeInsets.only( left: 140),
                              child: Row(
                                children: [
                                  Icon(
                                    Icons.mode_fan_off,
                                    size: 30,
                                    color: Colors.red,
                                  ),
                                  Icon(
                                    Icons.mode_fan_off,
                                    size: 60,
                                    color: Colors.red,
                                  ),
                                  Icon(
                                    Icons.mode_fan_off,
                                    size: 90,
                                    color: Colors.red,
                                  ),
                                ],
                              )
                              
                            )
                          ],
                        ),
                      )
                    )
                  ],
                ),
              ),

              Container(
                height:  320,
                decoration: BoxDecoration(
                  color: Colors.blue,
                  borderRadius: BorderRadius.circular(5)
                ),
                child: Column(
                  children: [
                    Padding(
                      padding: const EdgeInsets.only(right: 0, top: 70),
                      child: InkWell(
                        onTap: () {
                          // ĐÂY LÀ NƠI XỬ LÍ SỰ KIỆN KHI BUTTON ĐƯỢC THAO TÁC
                        },
                        child: Ink(
                          width: 100,
                          height: 70,
                          decoration: const BoxDecoration(
                            color: Colors.white,
                          ),
                          child: Row(
                            mainAxisAlignment: MainAxisAlignment.center,
                            children: [
                              Icon(
                                Icons.arrow_upward,
                                color: Colors.white,
                              ),
                              const Text('up', style: TextStyle(color: Colors.white)),
                            ],
                          ),
                        ),
                      ),
                    ),
                      
                     Row(
                       children: [
                         Padding(
                           padding: const EdgeInsets.only( left: 78),
                           child: ElevatedButton(onPressed: () {
                                    // ĐÂY LÀ NƠI XỬ LÍ SỰ KIỆN KHI BUTTON ĐƯỢC THAO TÁC
                            },
                            style: ButtonStyle(
                              minimumSize: MaterialStateProperty.all( Size( 100, 70)),
                              backgroundColor: MaterialStateProperty.all( Colors.lime)
                            ),
                            child: Text( 'mode'),
                            ),
                         ),

                          ElevatedButton(onPressed: () {
                                  // ĐÂY LÀ NƠI XỬ LÍ SỰ KIỆN KHI BUTTON ĐƯỢC THAO TÁC
                          },
                          style: ButtonStyle(
                            minimumSize: MaterialStateProperty.all( Size( 100, 70)),
                            backgroundColor: MaterialStateProperty.all( Colors.teal)
                          ),
                          child: Text( 'F/C'),
                          ),

                          ElevatedButton(onPressed: () {
                                  // ĐÂY LÀ NƠI XỬ LÍ SỰ KIỆN KHI BUTTON ĐƯỢC THAO TÁC
                          },
                          style: ButtonStyle(
                            minimumSize: MaterialStateProperty.all( Size( 100, 70)),
                            backgroundColor: MaterialStateProperty.all( Colors.white30)
                          ),
                          child: Text( 'fan'),
                          ),
                       ],
                     ),

                      ElevatedButton(onPressed: () {
                              // ĐÂY LÀ NƠI XỬ LÍ SỰ KIỆN KHI BUTTON ĐƯỢC THAO TÁC
                      },
                      style: ButtonStyle(
                        minimumSize: MaterialStateProperty.all( Size( 100, 70)),
                        backgroundColor: MaterialStateProperty.all( Colors.deepPurple)
                      ),
                      child: Text( 'down'),
                      ),
                    
                  ],
                ),
              ),
            ],
          )
      ),
    );
  }
}
