class Tree:
    nodes = []
    links = []

    def __init__(self):
        self.nodes = []
        self.links = []

    def size(self) -> int:
        return len(self.nodes)
    
    def add_node(self, new_value):
        index = 0
        l = self.size()

        if l == 0:
            self.nodes = [new_value]
            self.links = [[-1, -1]]

        while index < l:
            if self.nodes[index] > new_value:
                if self.links[index][0] == -1:
                    self.nodes.append(new_value)
                    self.links.append([-1, -1])
                    self.links[index][0] = l
                    break
                else:
                    index = self.links[index][0]
            else:
                if self.links[index][1] == -1:
                    self.nodes.append(new_value)
                    self.links.append([-1, -1])
                    self.links[index][1] = l
                else:
                    index = self.links[index][1]

    def read_from_file(self, file_name):
        file = open(file_name, "r")
        data = file.readlines()
        file.close()

        data_simplified = []

        for elem in data:
            value = int(list(elem.split())[1])
            data_simplified.append(value)
            self.add_node(value)
        
            
    
    def count_leaves(self) -> int:
        l = self.size()
        count = 0

        for i in range(l):
            if (self.links[i][0] == -1 and self.links[i][1] == -1):
                count += 1
        
        return count
    
    # список глубин поддеревьев + фиктивный 0 на конце
    def subtrees_depths(self):
        l = self.size()
        depths = [0] * (l + 1)
        depth = 0

        for i in range(l - 1, -1, -1):
            depth = max(depths[self.links[i][0]], depths[self.links[i][1]])
            depths[i] = 1 + depth

        #print(depths)
        return depths
    
    def vertices_levels(self):
        l = self.size()
        level = [0] * (l + 1)

        level[0] = 0
        for i in range(0, l):
            level[self.links[i][0]] = 1 + level[i]
            level[self.links[i][1]] = 1 + level[i]

        return level[0:l]
    
    def depth(self) -> int:
        return self.subtrees_depths()[0]
    
    def max_level_size(self) -> int:
        l = self.size()
        levels = [0] * l
        depths = self.vertices_levels()

        for i in range(l - 1, -1, -1):
            levels[depths[i] - 1] += 1
        
        return max(levels)
    
    def depths_difference(self) -> int:
        maximum = 0
        l = self.size()
        depths = self.subtrees_depths()

        for i in range(l):
            diff = abs(depths[self.links[i][0]] - depths[self.links[i][1]])
            maximum = max(maximum, diff)
        
        return maximum

    def count_with_one_child(self) -> int:
        count = 0
        l = self.size()

        for i in range(l):
            if ((self.links[i][0] == -1 and self.links[i][1] != -1)
                or (self.links[i][0] != -1 and self.links[i][1] == -1)):
                    count += 1
        
        return count