CPP = g++ -Wall  -Wextra -Wconversion -g -lm
OUT = diseaseMonitor
DATA = small.txt

OBJS = main.o PatientRecord.o MyDate.o MyBST.o DCHashTable.o DiseaseMonitor.o TopkArrayList.o TopkMaxHeap.o

$(OUT): $(OBJS)
	$(CPP) $^ -o $@

%.o: %.cpp %.h
	$(CPP) -c $<

%.o: %.cpp
	$(CPP) -c $<

run:
	./$(OUT) -p $(DATA) -h1 10 -h2 10 -b 128

val: 
	valgrind -v --leak-check=full --show-leak-kinds=all ./$(OUT) -p $(DATA) -h1 2 -h2 2 -b 256

clean:
	rm -f $(OBJS) $(OUT)