import re
from collections import Counter
import matplotlib.pyplot as plt
import seaborn as sns

def parse_trace(trace_file):
    with open(trace_file, 'r') as f:
        return f.read()

def extract_operations(trace_content):
    pattern = r'(OP: )(\w+)'
    return [match.group(2) for match in re.finditer(pattern, trace_content)]

def count_individual_operations(operations):
    return Counter(op for op in operations)

def count_operation_sequences(operations, max_length=5):
    if isinstance(operations[0], tuple):
        # Convert tuples to strings
        operations = [''.join(op) for op in operations]
    
    sequences = []
    for i in range(len(operations) - max_length + 1):
        seq = ' '.join(operations[i:i+max_length])
        sequences.append(seq)
    return Counter(sequences)

def plot_individual_hist(individual_counts):
    plt.figure(figsize=(12, 6))
    
    # Plot histogram for individual operations
    sns.barplot(x=individual_counts.keys(), y=individual_counts.values(), palette="Blues_d")
    plt.title("Histogram of Individual Operations")
    plt.xlabel("Operation")
    plt.ylabel("Count")
    plt.xticks(rotation=45)
    plt.tight_layout()
    plt.show()

def plot_sequence_hist(sequence_counts):

    # Plot histogram for operation sequences
    sequence_counts_top_5 = sequence_counts.most_common(10)
    sequence_names = [f"{seq}" for seq, _ in sequence_counts_top_5]
    sequence_counts_top_5 = dict(sequence_counts_top_5)
    
    sns.barplot(x=sequence_names, y=list(sequence_counts_top_5.values()), palette="Greens_d")
    plt.title("Top 5 Sequences of Operations")
    plt.xlabel("Sequence Description")
    plt.ylabel("Count")
    plt.xticks(rotation=45)
    plt.tight_layout()
    plt.show()

def main():
    trace_file = "./log.txt"  # Replace with your actual trace file name
    
    # Parse the trace file
    trace_content = parse_trace(trace_file)
    
    # Extract operations
    operations = extract_operations(trace_content)
    
    print(f"Extracted operations: {operations[:10]}...")  # Print first 10 operations
    
    # Count individual operations
    individual_counts = count_individual_operations(operations)
    plot_individual_hist(individual_counts)

    # Count operation sequences
    sequence_counts = count_operation_sequences(operations, max_length=1)
    plot_sequence_hist(sequence_counts)
    print(sequence_counts)

    sequence_counts = count_operation_sequences(operations, max_length=2)
    plot_sequence_hist(sequence_counts)
    print(sequence_counts)

    sequence_counts = count_operation_sequences(operations, max_length=3)
    plot_sequence_hist(sequence_counts)
    print(sequence_counts)


    sequence_counts = count_operation_sequences(operations, max_length=4)
    plot_sequence_hist(sequence_counts)
    print(sequence_counts)

    sequence_counts = count_operation_sequences(operations, max_length=5)
    plot_sequence_hist(sequence_counts)
    print(sequence_counts)

    print(f"Number of operations: {len(operations)}")
    print(f"Number of unique operations: {len(set(operations))}")
    
if __name__ == "__main__":
    main()
