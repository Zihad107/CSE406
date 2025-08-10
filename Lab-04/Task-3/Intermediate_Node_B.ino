#include <painlessMesh.h>

#define MESH_PREFIX     "cse406"
#define MESH_PASSWORD   "summer25"
#define MESH_PORT       5555

Scheduler userScheduler;
painlessMesh mesh;

// Relay node: do not display messages
void receivedCallback(uint32_t from, String &msg) {
  // Silent relay, optional debug only
  Serial.printf("🔗 Relay Node B connected. (Not displaying messages)\n");
}

void newConnectionCallback(uint32_t nodeId) {
  Serial.printf("🔗 Node B Connected with Node ID: %u\n", nodeId);
}

void setup() {
  Serial.begin(115200);
  mesh.setDebugMsgTypes(ERROR | STARTUP | CONNECTION);  

  mesh.init(MESH_PREFIX, MESH_PASSWORD, &userScheduler, MESH_PORT);

  mesh.onReceive(&receivedCallback);
  mesh.onNewConnection(&newConnectionCallback);

  Serial.printf("✅ Relay Node B Ready | My Node ID: %u\n", mesh.getNodeId());
}

void loop() {
  mesh.update();
}
