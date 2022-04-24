import 'package:flutter/material.dart';
import 'package:smart_water_motor/components/reusable_card.dart';
import '../constants.dart';
import '../components/bottom_button.dart';

class ProjectPage extends StatelessWidget {
  @override
  Widget build(BuildContext context) {
    return Scaffold(
      appBar: AppBar(
        title: Text(
          'SMART WATER MOTOR',
          style: kHeadingTextStyle,
        ),
      ),
      body: Column(
        mainAxisAlignment: MainAxisAlignment.spaceEvenly,
        crossAxisAlignment: CrossAxisAlignment.stretch,
        children: [
          Expanded(
            child: Container(
              padding: EdgeInsets.all(15.0),
              alignment: Alignment.bottomLeft,
              child: Text(
                'Project Details',
                style: kProjectTitleTextStyle,
              ),
            ),
          ),
          Expanded(
            flex: 5,
            child: ReusableCard(
              colour: kActiveCardColor,
              cardChild: Column(
                mainAxisAlignment: MainAxisAlignment.spaceEvenly,
                crossAxisAlignment: CrossAxisAlignment.center,
                children: [
                  Text(
                    'Group members',
                    style: kProjectHeadingText,
                  ),
                  Column(
                    children: [
                      Text(
                        'Reedam Ranjan : 1805686',
                        style: kLabelTextStyle,
                      ),
                      SizedBox(
                        height: 5.0,
                      ),
                      Text(
                        'Samridhi Wadhwa : 1805154',
                        style: kLabelTextStyle,
                      ),
                      SizedBox(
                        height: 5.0,
                      ),
                      Text(
                        'Nandini Kalita : 1805675',
                        style: kLabelTextStyle,
                      ),
                      SizedBox(
                        height: 5.0,
                      ),
                      Text(
                        'Surodeep Dhar : 1805711',
                        style: kLabelTextStyle,
                      ),
                      SizedBox(
                        height: 5.0,
                      ),
                    ],
                  ),
                  Column(
                    children: [
                      Text(
                        'Project Guide',
                        style: kLabelTextStyle,
                      ),
                      Text(
                        'Asst. Prof. Chandini Kumari',
                        style: kLabelTextStyle,
                      ),
                    ],
                  ),
                ],
              ),
            ),
          ),
          BottomButton(onTap: (){Navigator.pop(context);},buttonTitle: 'Back To Reading',),
        ],
      ),
    );
  }
}
