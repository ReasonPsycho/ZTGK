//
// Created by cheily on 20.03.2024.
//

#include "SignalReceiver.h"
#include "Systems/Util.h"

using namespace ztgk_util;

SignalReceiver::SignalReceiver() : SignalReceiver(0) {}

SignalReceiver::SignalReceiver(unsigned int receiveTypeMask) : uid(id<ID_POOL_COMPONENT>()),
                                                               receive_type_mask(receiveTypeMask) {}
