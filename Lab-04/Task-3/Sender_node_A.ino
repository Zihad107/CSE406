#include <painlessMesh.h>

// Mesh network configuration
#define MESH_PREFIX     "cse406"
#define MESH_PASSWORD   "summer25"
#define MESH_PORT       5555

Scheduler userScheduler;
painlessMesh mesh;

// === Target Node ID (Node C) ===
uint32_t targetNodeId = 1163270074;  // Receiver C

// === Message sending function declaration ===
void sendMessage(); 
Task taskSendMessage(TASK_SECOND * 2 , TASK_FOREVER, &sendMessage);

// === Function that sends message to target node ===
void sendMessage() {
  String msg = "Hello from Node ";
  msg += mesh.getNodeId();   // Adds this device's Node ID
  msg += " 🚀 | Mesh network communication successful!";

  if (mesh.isConnected(targetNodeId)) {
    bool success = mesh.sendSingle(targetNodeId, msg);
    if (success) {
      Serial.printf("📤 Message sent to %u ✅\n", targetNodeId);
    } else {
      Serial.printf("❌ Failed to send to %u\n", targetNodeId);
    }
  } else {
    Serial.printf("⚠️ Target Node %u is not connected!\n", targetNodeId);
  }

  // Next message interval (2–6 seconds)
  taskSendMessage.setInterval(random(TASK_SECOND * 2, TASK_SECOND * 6));
}

// === Callback: Message Received ===
void receivedCallback(uint32_t from, String &msg) {
  Serial.println("====================================");
  Serial.printf("📩 Message received!\n");
  Serial.printf("👤 Sender Node ID : %u\n", from);
  Serial.printf("✉️  Message        : %s\n", msg.c_str());
  Serial.println("====================================\n");
}

// === Callback: New Connection ===
void newConnectionCallback(uint32_t nodeId) {
  Serial.printf("🔗 Connected with Node ID: %u\n", nodeId);
}

// === Callback: Topology Changed ===
void changedConnectionCallback() {
  Serial.println("🔄 Connection list changed");
}

// === Callback: Time Sync Offset ===
void nodeTimeAdjustedCallback(int32_t offset) {
  Serial.printf("⏱️ Time adjusted. Offset = %d\n", offset);
}

// === Arduino Setup ===
void setup() {
  Serial.begin(115200);

  // Enable detailed logs for Task 3
  mesh.setDebugMsgTypes(CONNECTION | COMMUNICATION | ERROR | STARTUP);

  // Initialize mesh network
  mesh.init(MESH_PREFIX, MESH_PASSWORD, &userScheduler, MESH_PORT);

  // Register callbacks
  mesh.onReceive(&receivedCallback);
  mesh.onNewConnection(&newConnectionCallback);
  mesh.onChangedConnections(&changedConnectionCallback);
  mesh.onNodeTimeAdjusted(&nodeTimeAdjustedCallback);

  // Start sending task
  userScheduler.addTask(taskSendMessage);
  taskSendMessage.enable();

  Serial.printf("✅ Sender Node A Ready | My Node ID: %u\n", mesh.getNodeId());
}

// === Arduino Loop ===
void loop() {
  mesh.update();
}
