#include <painlessMesh.h>

#define MESH_PREFIX     "cse406"
#define MESH_PASSWORD   "summer25"
#define MESH_PORT       5555

Scheduler userScheduler;
painlessMesh mesh;

// === TASK: Periodic print of own Node ID ===
void printNodeId();
Task taskPrintNodeId(TASK_SECOND * 10, TASK_FOREVER, &printNodeId); // every 10 sec

void printNodeId() {
  Serial.printf("ℹ️ [RECEIVER] My Node ID: %u\n", mesh.getNodeId());
}

// === Callback: Message received from sender ===
void receivedCallback(uint32_t from, String &msg) {
  Serial.println("====================================");
  Serial.printf("📩 Message received from Node %u\n", from);
  Serial.printf("✉️  Message        : %s\n", msg.c_str());
  Serial.println("====================================\n");

  // Send ACK back to sender
  String ack = "✅ ACK from Node " + String(mesh.getNodeId());
  mesh.sendSingle(from, ack);
  Serial.printf("📤 Sent ACK to Node %u\n", from);
}

void newConnectionCallback(uint32_t nodeId) {
  Serial.printf("🔗 Connected with Node ID: %u\n", nodeId);
}

void setup() {
  Serial.begin(115200);
  mesh.setDebugMsgTypes(ERROR | STARTUP);

  mesh.init(MESH_PREFIX, MESH_PASSWORD, &userScheduler, MESH_PORT);
  mesh.onReceive(&receivedCallback);
  mesh.onNewConnection(&newConnectionCallback);

  userScheduler.addTask(taskPrintNodeId);
  taskPrintNodeId.enable();

  Serial.printf("✅ Receiver Ready | My Node ID: %u\n", mesh.getNodeId());
}

void loop() {
  mesh.update();
}
