# Standard flags

ifndef verbose
  SILENT = @
endif

CXX = g++
CXXFLAGS = -g -MMD
LINKERFLAGS = -lX11 -L/usr/X11R6/lib

OBJECTS = main.o GameManager.o PhysicsManager.o MapManager.o AIManager.o PlaneManager.o HelichopterManager.o WallObj.o TargetObj.o MissileObj.o HelichopterObj.o PlaneObj.o Objects.o ExplosiveObj.o ObjectsFactory.o

EXEC = x_game

#substitute ".o" with ".d"
DEPENDS = ${OBJECTS:.o=.d}

all: ${EXEC}

${EXEC}: ${OBJECTS}
	$(SILENT) ${CXX} ${OBJECTS} -o ${EXEC} ${CXXFLAGS} ${LINKERFLAGS}

run: ${EXEC}
	./${EXEC}

clean:
	rm -rf ${DEPENDS} ${OBJECTS} ${EXEC}

main.o: main.cpp
	@echo "building main"
	$(SILENT) $(CXX) $(CXXFLAGS) -o "$@" -MF $(@:%.o=%.d) -c "$<"

GameManager.o: GameManager.cpp
	@echo "building Game Manager"
	$(SILENT) $(CXX) $(CXXFLAGS) -o "$@" -MF $(@:%.o=%.d) -c "$<"

PhysicsManager.o: PhysicsManager.cpp
	@echo "building Physics Manager"
	$(SILENT) $(CXX) $(CXXFLAGS) -o "$@" -MF $(@:%.o=%.d) -c "$<"

MapManager.o: MapManager.cpp
	@echo "building Map Manager"
	$(SILENT) $(CXX) $(CXXFLAGS) -o "$@" -MF $(@:%.o=%.d) -c "$<"

AIManager.o: AIManager.cpp
	@echo "building AI Manager"
	$(SILENT) $(CXX) $(CXXFLAGS) -o "$@" -MF $(@:%.o=%.d) -c "$<"

PlaneManager.o: PlaneManager.cpp
	@echo "building Plane Manager"
	$(SILENT) $(CXX) $(CXXFLAGS) -o "$@" -MF $(@:%.o=%.d) -c "$<"

HelichopterManager.o: HelichopterManager.cpp
	@echo "building Helicopter Manager"
	$(SILENT) $(CXX) $(CXXFLAGS) -o "$@" -MF $(@:%.o=%.d) -c "$<"

WallObj.o: WallObj.cpp
	@echo "building Wall Objects"
	$(SILENT) $(CXX) $(CXXFLAGS) -o "$@" -MF $(@:%.o=%.d) -c "$<"

TargetObj.o: TargetObj.cpp
	@echo "building Target Objects"
	$(SILENT) $(CXX) $(CXXFLAGS) -o "$@" -MF $(@:%.o=%.d) -c "$<"

MissileObj.o: MissileObj.cpp
	@echo "building Missile Objects"
	$(SILENT) $(CXX) $(CXXFLAGS) -o "$@" -MF $(@:%.o=%.d) -c "$<"

HelichopterObj.o: HelichopterObj.cpp
	@echo "building Helicopter Objects"
	$(SILENT) $(CXX) $(CXXFLAGS) -o "$@" -MF $(@:%.o=%.d) -c "$<"

PlaneObj.o: PlaneObj.cpp
	@echo "building Plane Objects"
	$(SILENT) $(CXX) $(CXXFLAGS) -o "$@" -MF $(@:%.o=%.d) -c "$<"

ExplosiveObj.o: ExplosiveObj.cpp
	@echo "building Explosive Objects"
	$(SILENT) $(CXX) $(CXXFLAGS) -o "$@" -MF $(@:%.o=%.d) -c "$<"


Objects.o: Objects.cpp
	@echo "building Objects Base class"
	$(SILENT) $(CXX) $(CXXFLAGS) -o "$@" -MF $(@:%.o=%.d) -c "$<"

ObjectsFactory.o: ObjectsFactory.cpp
	@echo "building Objects Factory"
	$(SILENT) $(CXX) $(CXXFLAGS) -o "$@" -MF $(@:%.o=%.d) -c "$<"

# reads the .d files and reruns dependencies
-include ${DEPENDENTS}