bool isAReleased = false;
bool isBReleased = false;
bool isXReleased = false;
bool isYReleased = false;

bool isUpReleased = false;
bool isDownReleased = false;
bool isLeftReleased = false;
bool isRightReleased = false;

bool onUpRelease(bool up){
  if(up){
    isUpReleased = true;
    return false;
  }else if(isUpReleased){
    isUpReleased = false;
    return true;
  }
  return false;
}

bool onDownRelease(bool down){
  if(down){
    isDownReleased = true;
    return false;
  }else if(isDownReleased){
    isDownReleased = false;
    return true;
  }
  return false;
}

bool onLeftRelease(bool left){
  if(left){
    isLeftReleased = true;
    return false;
  }else if(isLeftReleased){
    isLeftReleased = false;
    return true;
  }
  return false;
}

bool onRightRelease(bool right){
  if(right){
    isRightReleased = true;
    return false;
  }else if(isRightReleased){
    isRightReleased = false;
    return true;
  }
  return false;
}

bool onARelease(bool a){
  if(a){
    isAReleased = true;
    return false;
  }else if(isAReleased){
    isAReleased = false;
    return true;
  }
  return false;
}

bool onBRelease(bool b){
  if(b){
    isBReleased = true;
    return false;
  }else if(isBReleased){
    isBReleased = false;
    return true;
  }
  return false;
}

bool onXRelease(bool x){
  if(x){
    isXReleased = true;
    return false;
  }else if(isXReleased){
    isXReleased = false;
    return true;
  }
  return false;
}

bool onYRelease(bool y){
  if(y){
    isYReleased = true;
    return false;
  }else if(isYReleased){
    isYReleased = false;
    return true;
  }
  return false;
}
