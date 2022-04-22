import 'package:flutter/material.dart';
import 'package:smart_water_motor/networking.dart';
import 'constants.dart';
import 'reusable_card.dart';
import 'project_page.dart';
import 'bottom_button.dart';
import 'package:http/http.dart' as http;
import 'api_model.dart';

class InputPage extends StatefulWidget {
  @override
  State<InputPage> createState() => _InputPageState();
}

class _InputPageState extends State<InputPage> {

  dynamic FlowSensor = NetworkHelper(url: kFlowSensorApi);
  dynamic RefreshValues =  NetworkHelper(url: kRefreshValuesApi);
  dynamic HandleRelay = NetworkHelper(url: kHandleRelayApi);
  dynamic RelayState = NetworkHelper(url: kRelaySateApi);
  dynamic TankPercentageLevel = NetworkHelper(url: kTankPercentageLevelApi);
  dynamic TankWaterLevel = NetworkHelper(url: kTankWaterLevelApi);
  dynamic SetTankCapacity = NetworkHelper(url: kSetTankCapacityApi);


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
                      On
                          ? Icon(
                              Icons.lightbulb,
                              size: 70.0,
                              color: Colors.amber,
                            )
                          : Icon(
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
                      Text('TANK CAPACITY', style: kLabelTextStyle),
                      Text(
                        '10 L',
                        style: kLabelTextStyle,
                      )
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
                        '$FlowSensor',
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
                          '$TankWaterLevel Litres',
                          style: kLabelTextStyle,
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
                          'Current Tank fill Level = $TankPercentageLevel% ',
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
