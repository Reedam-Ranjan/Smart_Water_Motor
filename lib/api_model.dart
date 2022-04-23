import 'package:flutter/material.dart';
import 'constants.dart';
import 'networking.dart';
import 'package:http/http.dart' as http;
import 'input_page.dart';

class ApiClass {

  Future getFlowReading() async {
    http.Response flowReading =
    await http.get(Uri.parse('http://192.168.0.149/readFlowSensor'));
    flow = flowReading.body.toString();
    print(flow);
    flow = '0';
    return flow;
  }

  Future getTankWaterLevel() async {
    http.Response tankWaterLevel =
    await http.get(Uri.parse('http://192.168.0.149/getTankWaterLevel'));
    level = tankWaterLevel.body.toString();
    print(level);
    return level;
  }

  Future getRefreshedValues() async {
    http.Response refreshValues =
    await http.get(Uri.parse('http://192.168.0.149/refreshValues'));
    refresh = refreshValues.body.toString();
    print(refresh);
    return refresh;
  }

  Future getTankPercentageLevel() async {
    http.Response tankPercentageLevel = await http
        .get(Uri.parse('http://192.168.0.149/getTankPercentageLevel'));
    percentage = tankPercentageLevel.body.toString();
    print(percentage);
    return percentage;
  }




  // Future getRefreshValues() async {
  //   dynamic RefreshValues = await NetworkHelper(url: kRefreshValuesApi);
  //   return RefreshValues;
  // }
  //
  // Future getHandleRelay() {
  //   dynamic HandleRelay = NetworkHelper(url: kHandleRelayApi);
  //   return HandleRelay;
  // }
  //
  // Future getRelayState() {
  //   dynamic RelayState = NetworkHelper(url: kRelaySateApi);
  //   return RelayState;
  // }
  //
  // Future getTankPercentageLevel() {
  //   dynamic TankPercentageLevel = NetworkHelper(url: kTankPercentageLevelApi);
  //   return TankPercentageLevel;
  // }
  //
  // Future getTankWaterLevel() {
  //   dynamic TankWaterLevel = NetworkHelper(url: kTankWaterLevelApi);
  // }
  //
  // Future setTankCapacity() {
  //   dynamic SetTankCapacity = NetworkHelper(url: kSetTankCapacityApi);
  //   return SetTankCapacity;
  // }
  //
  // Future getFlowSensor() {
  //   dynamic FlowSensor = NetworkHelper(url: kFlowSensorApi);
  //   return FlowSensor;
  // }

  @override
  Widget build(BuildContext context) {
    return Container();
  }
}

// dynamic FlowSensor = NetworkHelper(url: kFlowSensorApi);
// dynamic RefreshValues =  NetworkHelper(url: kRefreshValuesApi);
// dynamic HandleRelay = NetworkHelper(url: kHandleRelayApi);
// dynamic RelayState = NetworkHelper(url: kRelaySateApi);
// dynamic TankPercentageLevel = NetworkHelper(url: kTankPercentageLevelApi);
// dynamic TankWaterLevel = NetworkHelper(url: kTankWaterLevelApi);
// dynamic SetTankCapacity = NetworkHelper(url: kSetTankCapacityApi);
