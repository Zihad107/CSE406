#include <painlessMesh.h>

#define MESH_PREFIX     "cse406"
#define MESH_PASSWORD   "summer25"
#define MESH_PORT       5555

Scheduler userScheduler;
painlessMesh mesh;

// === TASK 1: Broadcast message sending ===
void sendMessage();
Task taskSendMessage(TASK_SECOND * 5, TASK_FOREVER, &sendMessage); // every 5 sec

void sendMessage() {
  String msg = "Hello from Node " + String(mesh.getNodeId()) + " 🌐";
  mesh.sendBroadcast(msg);
  Serial.println("📡 Broadcast message sent to all nodes.");
  taskSendMessage.setInterval(random(TASK_SECOND * 5, TASK_SECOND * 10));
}

// === TASK 2: Periodic print of own Node ID ===
void printNodeId();
Task taskPrintNodeId(TASK_SECOND * 10, TASK_FOREVER, &printNodeId); // every 10 sec

void printNodeId() {
  Serial.printf("ℹ️ [SENDER] My Node ID: %u\n", mesh.getNodeId());
}

// === Callback: Message received from receivers (ACK) ===
void receivedCallback(uint32_t from, String &msg) {
  Serial.println("====================================");
  Serial.printf("📥 ACK received from Node %u ✅\n", from);
  Serial.printf("✉️  Message        : %s\n", msg.c_str());
  Serial.println("====================================\n");
}

void newConnectionCallback(uint32_t nodeId) {
  Serial.printf("🔗 New Node Connected: %u\n", nodeId);
}

void setup() {
  Serial.begin(115200);
  mesh.setDebugMsgTypes(ERROR | STARTUP);

  mesh.init(MESH_PREFIX, MESH_PASSWORD, &userScheduler, MESH_PORT);
  mesh.onReceive(&receivedCallback);
  mesh.onNewConnection(&newConnectionCallback);

  userScheduler.addTask(taskSendMessage);
  userScheduler.addTask(taskPrintNodeId);
  taskSendMessage.enable();
  taskPrintNodeId.enable();

  Serial.printf("✅ Sender Ready | My Node ID: %u\n", mesh.getNodeId());
}

void loop() {
  mesh.update();
}
