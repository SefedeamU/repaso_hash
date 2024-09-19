#include <iostream>

//1.
class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        vector<int> rpta(2);
        unordered_map<int, int> a;
        for(int i=0;i<nums.size();i++){
            if(a.find(target-nums[i]) != a.end()){
                rpta[0] = i;
                rpta[1] = a[target - nums[i]];

            }else{
                a[nums[i]]=i;
            }
        }
        return rpta;
    }
};

//3.
class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        unordered_map<char, int> mapa;
        int maxLength = 0;
        int left = 0;

        for (int right = 0; right < s.length(); right++) {
            if (mapa.find(s[right]) != mapa.end()) {
                left = max(mapa[s[right]] + 1, left);
            }

            mapa[s[right]] = right;

            maxLength = max(maxLength, right - left + 1);
        }

        return maxLength;
    }
};

//12.
class Solution {
public:
    string intToRoman(int num) {
        vector<pair<int, string>> roman = {
            {1000, "M"}, {900, "CM"}, {500, "D"}, {400, "CD"},
            {100, "C"}, {90, "XC"}, {50, "L"}, {40, "XL"},
            {10, "X"}, {9, "IX"}, {5, "V"}, {4, "IV"}, {1, "I"}
        };

        string result = "";

        for (int i = 0; i < roman.size(); ++i) {
            int value = roman[i].first;
            string symbol = roman[i].second;

            while (num >= value) {
                result += symbol;
                num -= value;
            }
        }

        return result;
    }
};

//36.
class Solution {
public:

    bool isValidSudoku(vector<vector<char>>& board) {
        // Crear arreglos para almacenar los valores de filas, columnas y      sub-cuadros
        vector<set<char>> filas(9);
        vector<set<char>> columnas(9);
        vector<set<char>> subCuadros(9);

        // Recorrer el tablero de Sudoku
        for (int i = 0; i < 9; ++i) {
            for (int j = 0; j < 9; ++j) {
                char valor = board[i][j];
                // Solo nos interesan las celdas que están llenas (no vacías '.')
                if (valor != '.') {
                    // Verificar la fila
                    if (filas[i].count(valor)) {
                        return false;  // Número repetido en la fila
                    }
                    filas[i].insert(valor);

                    // Verificar la columna
                    if (columnas[j].count(valor)) {
                        return false;  // Número repetido en la columna
                    }
                    columnas[j].insert(valor);

                    // Verificar el sub-cuadro de 3x3
                    int indexSubCuadro = (i / 3) * 3 + (j / 3);
                    if (subCuadros[indexSubCuadro].count(valor)) {
                        return false;  // Número repetido en el sub-cuadro
                    }
                    subCuadros[indexSubCuadro].insert(valor);
                }
            }
        }
        // Si no encontramos ningún duplicado, el tablero es válido
        return true;
    }

};

//49.
class Solution {
public:
    vector<vector<string>> groupAnagrams(vector<string>& strs) {
        unordered_map<string, vector<string>> anagramGroups;

        for (string& word : strs) {
            string sortedWord = word;
            sort(sortedWord.begin(), sortedWord.end());

            anagramGroups[sortedWord].push_back(word);
        }

        vector<vector<string>> result;
        for (auto& group : anagramGroups) {
            result.push_back(group.second);
        }

        return result;
    }
};

//73.
class Solution {
public:
    void setZeroes(vector<vector<int>>& matrix) {
        int m = matrix.size();
        int n = matrix[0].size();
        bool firstRowZero = false;
        bool firstColZero = false;

        for (int j = 0; j < n; ++j) {
            if (matrix[0][j] == 0) {
                firstRowZero = true;
                break;
            }
        }

        for (int i = 0; i < m; ++i) {
            if (matrix[i][0] == 0) {
                firstColZero = true;
                break;
            }
        }

        for (int i = 1; i < m; ++i) {
            for (int j = 1; j < n; ++j) {
                if (matrix[i][j] == 0) {
                    matrix[i][0] = 0;
                    matrix[0][j] = 0;
                }
            }
        }

        for (int i = 1; i < m; ++i) {
            for (int j = 1; j < n; ++j) {
                if (matrix[i][0] == 0 || matrix[0][j] == 0) {
                    matrix[i][j] = 0;
                }
            }
        }

        if (firstRowZero) {
            for (int j = 0; j < n; ++j) {
                matrix[0][j] = 0;
            }
        }

        if (firstColZero) {
            for (int i = 0; i < m; ++i) {
                matrix[i][0] = 0;
            }
        }
    }
};

//128.
class Solution {
public:
    int longestConsecutive(vector<int>& nums) {
        unordered_map<int, bool> numMap;
        int longestStreak = 0;

        for (int num : nums) {
            numMap[num] = true;
        }

        for (int num : nums) {
            if (numMap[num]) {
                int currentNum = num;
                int currentStreak = 0;

                //Revisamos si se repite
                while (numMap.find(currentNum) != numMap.end()) {
                    numMap[currentNum] = false; // Check
                    currentNum += 1;
                    currentStreak += 1;
                }

                longestStreak = max(longestStreak, currentStreak);
            }
        }

        return longestStreak;
    }
};

//133.
class Solution {
public:
    Node* cloneGraph(Node* node) {
        if (node == nullptr) {
            return nullptr;
        }

        // Mapa para almacenar la correspondencia entre nodos originales y clonados
        unordered_map<Node*, Node*> map;
        return dfs(node, map);
    }

    Node* dfs(Node* node, unordered_map<Node*, Node*>& map) {
        // Si el nodo ya ha sido clonado, simplemente devuélvelo
        if (map.find(node) != map.end()) {
            return map[node];
        }

        // Crear un nuevo nodo clonado
        Node* clone = new Node(node->val);
        map[node] = clone;

        // Clonar los vecinos
        for (Node* neighbor : node->neighbors) {
            clone->neighbors.push_back(dfs(neighbor, map));
        }

        return clone;
    }
};

//139.
class Solution {
public:
    bool wordBreak(string s, vector<string>& wordDict) {
        unordered_set<string> wordSet(wordDict.begin(), wordDict.end());
        unordered_map<int, bool> memo;
        return canSegment(0, s, wordSet, memo);
    }

private:
    bool canSegment(int start, const string& s, const unordered_set<string>& wordSet, unordered_map<int, bool>& memo) {
        if (start == s.size()) return true;
        if (memo.count(start)) return memo[start];

        for (int end = start + 1; end <= s.size(); ++end) {
            if (wordSet.count(s.substr(start, end - start)) && canSegment(end, s, wordSet, memo)) {
                return memo[start] = true;
            }
        }

        return memo[start] = false;
    }
};

int main() {
    std::cout << "Hello, World!" << std::endl;
    return 0;
}
