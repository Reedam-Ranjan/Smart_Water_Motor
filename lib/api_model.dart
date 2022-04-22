import 'package:flutter/material.dart';
import 'constants.dart';
import 'networking.dart';

class ApiModel extends StatefulWidget {
  @override
  _ApiModelState createState() => _ApiModelState();
}

class _ApiModelState extends State<ApiModel> {
  Future getRefreshValues() async {
    dynamic RefreshValues = await NetworkHelper(url: kRefreshValuesApi);
    return RefreshValues;
  }

  Future getHandleRelay() {
    dynamic HandleRelay = NetworkHelper(url: kHandleRelayApi);
    return HandleRelay;
  }

  Future getRelayState() {
    dynamic RelayState = NetworkHelper(url: kRelaySateApi);
    return RelayState;
  }

  Future getTankPercentageLevel() {
    dynamic TankPercentageLevel = NetworkHelper(url: kTankPercentageLevelApi);
    return TankPercentageLevel;
  }

  Future getTankWaterLevel() {
    dynamic TankWaterLevel = NetworkHelper(url: kTankWaterLevelApi);
  }

  Future setTankCapacity() {
    dynamic SetTankCapacity = NetworkHelper(url: kSetTankCapacityApi);
    return SetTankCapacity;
  }

  Future getFlowSensor() {
    dynamic FlowSensor = NetworkHelper(url: kFlowSensorApi);
    return FlowSensor;
  }

  @override
  Widget build(BuildContext context) {
    return Container();
  }
}

dynamic FlowSensor = NetworkHelper(url: kFlowSensorApi);
dynamic RefreshValues =  NetworkHelper(url: kRefreshValuesApi);
dynamic HandleRelay = NetworkHelper(url: kHandleRelayApi);
dynamic RelayState = NetworkHelper(url: kRelaySateApi);
dynamic TankPercentageLevel = NetworkHelper(url: kTankPercentageLevelApi);
dynamic TankWaterLevel = NetworkHelper(url: kTankWaterLevelApi);
dynamic SetTankCapacity = NetworkHelper(url: kSetTankCapacityApi);
