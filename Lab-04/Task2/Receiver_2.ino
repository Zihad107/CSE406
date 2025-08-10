#include <painlessMesh.h>

#define MESH_PREFIX     "cse406"
#define MESH_PASSWORD   "summer25"
#define MESH_PORT       5555

Scheduler userScheduler;
painlessMesh mesh;

void receivedCallback(uint32_t from, String &msg) {
  Serial.println("====================================");
  Serial.printf("📩 Message received!\n");
  Serial.printf("👤 Sender Node ID : %u\n", from);
  Serial.printf("✉️  Message        : %s\n", msg.c_str());
  Serial.println("====================================\n");
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

  Serial.printf("✅ Receiver Ready | My Node ID: %u\n", mesh.getNodeId());
}

void loop() {
  mesh.update();
}