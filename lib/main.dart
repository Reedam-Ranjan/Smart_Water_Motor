import 'package:flutter/material.dart';
import 'input_page.dart';

void main() => runApp(SmartWaterMotor());

class SmartWaterMotor extends StatelessWidget {
  @override
  Widget build(BuildContext context) {
    return MaterialApp(
      theme: ThemeData.dark().copyWith(
        primaryColorLight: Colors.red,
        scaffoldBackgroundColor: Color(0xFF0A0E21),
      ),
      home: InputPage(),
    );
  }
}
