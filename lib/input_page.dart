import 'package:flutter/material.dart';
import 'package:smart_water_motor/services/networking.dart';
import 'constants.dart';
import 'components/reusable_card.dart';
import 'screens/project_page.dart';
import 'components/bottom_button.dart';
import 'package:http/http.dart' as http;
import 'services/api_model.dart';
import 'dart:math';

class InputPage extends StatefulWidget {
  @override
  State<InputPage> createState() => _InputPageState();
}

String flowReading;
String tankWaterLevel;
String tankPercentageLevel;
String flow;
String level;
String percentage;
String refresh;

class _InputPageState extends State<InputPage> {
  ApiClass api = ApiClass();
  int flower = 0;


//   Future<String> getFlowReading() async{
//     String flowReading = await NetworkHelper(url: kFlowSensorApi).toString();
//     return flowReading;
//   }
// Future<String> getTankWaterLevel() async{
//     String tankWaterLevel = await NetworkHelper(url: kTankWaterLevelApi).toString();
//     return tankWaterLevel;
//   }
// Future<String> getTankPercentageLevel() async{
//     String  tankPercentageLevel = await NetworkHelper(url: kTankPercentageLevelApi).toString();
//     return tankPercentageLevel;
//   }

  // dynamic FlowSensor = NetworkHelper(url: kFlowSensorApi);
  // dynamic RefreshValues =  NetworkHelper(url: kRefreshValuesApi);
  // dynamic HandleRelay = NetworkHelper(url: kHandleRelayApi);
  // dynamic RelayState = NetworkHelper(url: kRelaySateApi);
  // dynamic TankPercentageLevel = NetworkHelper(url: kTankPercentageLevelApi);
  // dynamic TankWaterLevel = NetworkHelper(url: kTankWaterLevelApi);
  // dynamic SetTankCapacity = NetworkHelper(url: kSetTankCapacityApi);

  bool On = false;
  @override
  Widget build(BuildContext context) {
    return Scaffold(
      appBar: AppBar(
        title: const Text(
          'SMART WATER MOTOR',
          style: kHeadingTextStyle,
        ),
      ),
      body: Column(
        crossAxisAlignment: CrossAxisAlignment.stretch,
        children: [
          Expanded(
              child: Row(
            children: [
              Expanded(
                child: ReusableCard(
                  colour: kActiveCardColor,
                  cardChild: Column(
                    mainAxisAlignment: MainAxisAlignment.center,
                    children: [
                      On? Icon(
                        Icons.lightbulb,
                        size: 70.0,
                        color: Colors.amber,
                      ) : Icon(
                        Icons.lightbulb_outline,
                        size: 70.0,
                        color: Colors.amber,
                      ),
                      ElevatedButton(
                          style: TextButton.styleFrom(
                            backgroundColor: Colors.green,
                          ),
                          onPressed: () {
                            setState(() {
                              On = !On;
                              // api.getFlowReading();
                              flower=0;
                              level = 1.00.toString();
                              percentage =100.toString();

                            });
                          },
                          child: On ? Text('On') : Text('Off'))
                    ],
                  ),
                ),
              ),
              Expanded(
                child: ReusableCard(
                  colour: kActiveCardColor,
                  cardChild: Column(
                    mainAxisAlignment: MainAxisAlignment.center,
                    children: [
                      Icon(
                        Icons.refresh_outlined,
                        size: 70.0,
                        color: Colors.green,
                      ),
                      ElevatedButton(
                        style: TextButton.styleFrom(
                          backgroundColor: Colors.green,
                        ),
                        onPressed: (){
                          setState(() {
                            flower = Random().nextInt(10);

                          });
                        },
                        child: Text('refresh'),
                        ),
                    ],
                  ),
                ),
              ),
            ],
          )),
          Expanded(
            child: ReusableCard(
              colour: kActiveCardColor,
              cardChild: Column(
                mainAxisAlignment: MainAxisAlignment.center,
                children: [
                  Text(
                    'Water Flow Rate',
                    style: kLabelTextStyle,
                  ),
                  SizedBox(
                    height: 10.0,
                  ),
                  Row(
                    mainAxisAlignment: MainAxisAlignment.center,
                    crossAxisAlignment: CrossAxisAlignment.baseline,
                    textBaseline: TextBaseline.alphabetic,
                    children: [
                      Text(
                        // http.get(Uri.parse(kFlowSensorApi)).toString(),
                        '$flower',
                        style: kNumberedTextStyle,
                      ),
                      Text(
                        'Liters/Hour',
                        style: kLabelTextStyle,
                      ),
                    ],
                  ),
                ],
              ),
            ),
          ),
          Expanded(
            child: Row(
              children: [
                Expanded(
                  child: ReusableCard(
                    colour: kActiveCardColor,
                    cardChild: Column(
                      mainAxisAlignment: MainAxisAlignment.center,
                      children: [
                        Icon(
                          Icons.battery_full_outlined,
                          size: 70.0,
                          color: Colors.lightBlue,
                        ),
                        SizedBox(
                          height: 10.0,
                        ),
                        Text(
                          'Current Water Level',
                          style: kLabelTextStyle,
                        ),
                        Text(
                          // http.get(Uri.parse(kTankWaterLevelApi)).toString(),
                          '$level litres',
                          style: kLabelTextStyle,
                          textAlign: TextAlign.center,
                        ),
                      ],
                    ),
                  ),
                ),
                Expanded(
                  child: ReusableCard(
                    colour: kActiveCardColor,
                    cardChild: Column(
                      mainAxisAlignment: MainAxisAlignment.center,
                      children: [
                        Icon(
                          Icons.battery_full_outlined,
                          size: 70.0,
                          color: Colors.lightBlue,
                        ),
                        SizedBox(
                          height: 10.0,
                        ),
                        Text(
                          // http.get(Uri.parse(kTankPercentageLevelApi)).toString(),
                          'Current Tank Fill Level = $percentage %',
                          style: kLabelTextStyle,
                          textAlign: TextAlign.center,
                        ),
                        // Text('100 %',style: kLabelTextStyle,
                        // textAlign: TextAlign.center,),
                      ],
                    ),
                  ),
                ),
              ],
            ),
          ),
          BottomButton(
            onTap: () {
              Navigator.push(context,
                  MaterialPageRoute(builder: (context) => ProjectPage()));
            },
            buttonTitle: 'Project Details',
          ),
        ],
      ),
    );
  }
}
